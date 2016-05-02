
#ifndef __DIFFIE_HELLMAN_H__
#define __DIFFIE_HELLMAN_H__

#include "ULong.h"

namespace DiffieHellmanLib
{
	template<size_t PModuleLength> class DiffieHellman
	{
	public:
		DiffieHellman(const vector<char> cryptoPModule, unsigned long cryptoGModule)
		{
			if (cryptoPModule.size() != PModuleLength) {
				throw exception("Неверный размер cryptoPModule.");
			}
			m_pCryptoPModule = cryptoPModule;
			m_pCryptoGModule = cryptoGModule;
		}

		bool GenerateExchangeData(vector<char>& externalData)
		{
			ULong<PModuleLength> g(m_pCryptoGModule);
			ULong<PModuleLength> p(&m_pCryptoPModule.front(), PModuleLength);

			vector<char> xBuff;
			if (!GenerateRandomX(xBuff)) {
				return false;
			}

			if (xBuff.size() <= PModuleLength) {
				InvertBinary(xBuff);

				m_X = ULong<PModuleLength>(&xBuff.front(), PModuleLength);
				ULong<PModuleLength> y = ApowBmodN(g, m_X, p);
				y.GetBinary(externalData);

				return true;
			}

			return false;
		}

		bool CompleteExchangeData(const vector<char>& externalData, vector<char>& sharedKey)
		{
			if (externalData.size() <= PModuleLength) {
				ULong<PModuleLength> p(&m_pCryptoPModule.front(), PModuleLength);
				ULong<PModuleLength> extData(&externalData.front(), PModuleLength);
				ULong<PModuleLength> y = ApowBmodN(extData, m_X, p);
				y.GetBinary(sharedKey);
				return true;
			}

			return false;
		}

	private:
		vector<char> m_pCryptoPModule;
		unsigned long m_pCryptoGModule;
		ULong<PModuleLength> m_X;

		bool GenerateRandomX(vector<char>& xBuff) {
			HCRYPTPROV provider;
			if (!CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL, NULL)) {
				if (!CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
					return false;
				}
			}
			xBuff.clear();
			xBuff.resize(PModuleLength);
			if (!CryptGenRandom(provider, PModuleLength / 4, (BYTE*)&xBuff.front())) {
				return false;
			}

			return true;
		}

		ULong<PModuleLength> ApowBmodN(const ULong<PModuleLength>& a, const ULong<PModuleLength>& b, const ULong<PModuleLength>& n) {
			ULong<PModuleLength> result = 1;
			ULong<PModuleLength> counter = b;
			ULong<PModuleLength> base = a;

			while (counter != 0) {
				if (counter.IsEvenNumber()) {
					counter /= 2;
					base.MultiplyAmodB(base, n);
				}
				else {
					counter--;
					result.MultiplyAmodB(base, n);
				}
			}
			return result;
		}

		void InvertBinary(vector<char>& binary) {
			size_t capacity = binary.size();
			for (size_t i = 0; i < capacity / 2; ++i) {
				char tmp = binary[i];
				binary[i] = binary[capacity - i - 1];
				binary[capacity - i - 1] = tmp;
			}
		}
	};
}
#endif //__DIFFIE_HELLMAN_H__