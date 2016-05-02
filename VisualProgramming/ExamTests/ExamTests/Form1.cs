using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SQLite;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Windows.Forms;

namespace ExamTests
{
    public partial class Form1 : Form
    {
        private int currentState;
        private int ticketsCount;

        private const int questionsCount = 2; // в БД строго определено количество
        private const int exercisesCount = 1; // вопросов и задач для одного билета

        private SQLiteConnection connect = new SQLiteConnection("Data Source=ExamTests.db");        

        public Form1()
        {            
            InitializeComponent();

            currentState = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            connect.Open();            

            listBox1.Items.Add("Билеты по всем темам");

            SQLiteCommand command;
            command = new SQLiteCommand("select name from Subjects", connect);
            try
            {
                SQLiteDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    listBox1.Items.Add(reader[0]);
                }
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }

            listBox1.SelectedIndex = 0;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void createAllTicketsPanel()
        {
            this.panel2.Visible = true;
            this.button2.Text = "Печать";

            label2.Text = "Для выбора нужного билета нажмите на соответствующий номер." +
                          " Для просмотра вопросов и задач в билете передвигайте полосу" +
                          " прокрутки. Чтобы отправить билеты на печать нажмите на" +
                          " кнопку \"Печать\".";

            SQLiteCommand command;
            command = new SQLiteCommand("select count(ticket_id) from Tickets", connect);
            try {
                SQLiteDataReader reader = command.ExecuteReader();
                reader.Read();
                ticketsCount = Convert.ToInt32(reader[0]);
            }
            catch (System.Data.SQLite.SQLiteException ex) {
                MessageBox.Show(ex.Message);
            }

            TabPage ticketsTabPage;
            RichTextBox ticketsRichTextBox;

            int ticketContentCount = questionsCount + exercisesCount;
            string[] ticketContentTitle = new String[ticketContentCount];
            string[] ticketContentText = new String[ticketContentCount];

            int querysForTicketCount = 3;
            string[] querysForTicketContent = new String[querysForTicketCount];
            querysForTicketContent[0] = "select t2.title, t2.text from Tickets t1 inner join Questions t2 " +
                                       "on t1.question1 = t2.question_id where t1.ticket_id=:value1";
            querysForTicketContent[1] = "select t2.title, t2.text from Tickets t1 inner join Questions t2 " +
                                       "on t1.question2 = t2.question_id where t1.ticket_id=:value1";
            querysForTicketContent[2] = "select t2.title, t2.text from Tickets t1 inner join Exercises t2 " +
                                       "on t1.exercise = t2.exercise_id where t1.ticket_id=:value1";

            for (int i = 0; i < ticketsCount; i++)
            {
                for (int j = 0; j < querysForTicketCount; j++)
                {
                    command = new SQLiteCommand(querysForTicketContent[j], connect);
                    command.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                    command.Parameters[0].Value = i + 1;
                    try
                    {
                        SQLiteDataReader reader = command.ExecuteReader();
                        reader.Read();
                        ticketContentTitle[j] = reader[0].ToString();
                        ticketContentText[j] = reader[1].ToString();
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }

                ticketsTabPage = new TabPage((i + 1).ToString());
                tabControl1.TabPages.Add(ticketsTabPage);

                string ticketText = "[Вопрос №1: " +
                                    ticketContentTitle[0] + "]\n" +
                                    ticketContentText[0] + "\n\n" +
                                    "[Вопрос №2: " +
                                    ticketContentTitle[1] + "]\n" +
                                    ticketContentText[1] + "\n\n" +
                                    "[Задача: " +
                                    ticketContentTitle[2] + "]\n" +
                                    ticketContentText[2];

                ticketsRichTextBox = new RichTextBox();
                ticketsRichTextBox.BackColor = button1.BackColor;
                ticketsRichTextBox.ReadOnly = true;
                ticketsRichTextBox.Location = new Point(0, 5);
                ticketsRichTextBox.Size = new Size(590, 290);
                ticketsRichTextBox.Text = ticketText;
                tabControl1.TabPages[i].Controls.Add(ticketsRichTextBox);
            }
        }

        private void createSubjectQuestionsPanel(int subject)
        {
            this.panel2.Visible = true;
            this.button2.Text = "Печать";

            label2.Text = "Для выбора нужного вопроса нажмите на соответствующий номер." +
                          " Для просмотра содержимого вопросов передвигайте полосу" +
                          " прокрутки. Чтобы отправить вопрос на печать нажмите на" +
                          " кнопку \"Печать\".";

            TabPage questionsTabPage;
            RichTextBox questionsRichTextBox;

            int i = 0;

            SQLiteCommand command;
            command = new SQLiteCommand("select question_id, title, text from Questions where Subject=:value1", connect);
            command.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
            command.Parameters[0].Value = subject;
            try
            {
                SQLiteDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    questionsTabPage = new TabPage((i + 1).ToString());
                    tabControl1.TabPages.Add(questionsTabPage);

                    string questionText = "[Вопрос №" +
                                    reader[0] + ": " +
                                    reader[1] + "]\n" +
                                    reader[2];

                    questionsRichTextBox = new RichTextBox();
                    questionsRichTextBox.BackColor = button1.BackColor;
                    questionsRichTextBox.ReadOnly = true;
                    questionsRichTextBox.Location = new Point(0, 5);
                    questionsRichTextBox.Size = new Size(590, 290);
                    questionsRichTextBox.Text = questionText;
                    tabControl1.TabPages[i].Controls.Add(questionsRichTextBox);
                    i++;
                }

                if (i == 0)
                {
                    MessageBox.Show("Для этой темы еще нет вопросов.");
                    button1.PerformClick();
                }
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void nextToolStripMenuItem_Click(object sender, EventArgs e)
        {
            switch (currentState) {
                case 0:
                    if (listBox1.SelectedIndex == -1) {
                        MessageBox.Show("Сначала выберите тему.", "Составление билетов", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    }
                    else {
                        panel1.Visible = false;

                        prevToolStripMenuItem.Enabled = true;
                        button1.Visible = true;                        
                        currentState++;

                        switch (listBox1.SelectedIndex) {
                            case 0:                                
                                createAllTicketsPanel();
                                break;
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                                createSubjectQuestionsPanel(listBox1.SelectedIndex);
                                break;
                            default:
                                MessageBox.Show("Для этой темы еще ничего нет.", "Составление билетов", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                                break;
                        }
                    }
                    break;

                case 1:
                    //currentState++;                    
                    Form2 printForm = new Form2();
                    if (printForm != null)
                    {
                        SQLiteCommand command;
                        string printText = "";
                        string[] tmpStringArray;

                        switch (listBox1.SelectedIndex)
                        {
                            case 0:                                
                                int printContentCount = questionsCount + exercisesCount;
                                string[] printContentTitle = new String[printContentCount];
                                string[] printContentText = new String[printContentCount];

                                int querysForPrintCount = 3;
                                string[] querysForPrintContent = new String[querysForPrintCount];

                                querysForPrintContent[0] = "select t2.title, t2.text from Tickets t1 inner join Questions t2 " +
                                                           "on t1.question1 = t2.question_id where t1.ticket_id=:value1";
                                querysForPrintContent[1] = "select t2.title, t2.text from Tickets t1 inner join Questions t2 " +
                                                           "on t1.question2 = t2.question_id where t1.ticket_id=:value1";
                                querysForPrintContent[2] = "select t2.title, t2.text from Tickets t1 inner join Exercises t2 " +
                                                           "on t1.exercise = t2.exercise_id where t1.ticket_id=:value1";

                                for (int j = 0; j < querysForPrintCount; j++)
                                {
                                    command = new SQLiteCommand(querysForPrintContent[j], connect);
                                    command.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                                    command.Parameters[0].Value = tabControl1.SelectedIndex + 1;
                                    try
                                    {
                                        SQLiteDataReader reader = command.ExecuteReader();
                                        reader.Read();
                                        printContentTitle[j] = reader[0].ToString();
                                        printContentText[j] = reader[1].ToString();
                                    }
                                    catch (System.Data.SQLite.SQLiteException ex)
                                    {
                                        MessageBox.Show(ex.Message);
                                    }
                                }
                                
                                printText = "                                                                                                    \n" +
                                            "                                Сибирский Государственный Университет Телекоммуникаций и Информатики\n" +
                                            "\n" +
                                            "                                                                                           Билет № " +
                                            (tabControl1.SelectedIndex + 1).ToString() + "\n";

                                for (int j = 0; j < querysForPrintCount; j++)
                                {
                                    printText = printText + "\n" + (j + 1) + ") ";

                                    tmpStringArray = ExtentionString.SplitByLength(printContentTitle[j], 136).ToArray();
                                    for (int k = 0; k < tmpStringArray.Length; k++)
                                    {
                                        printText = printText + tmpStringArray[k] + "\n";
                                    }

                                    tmpStringArray = ExtentionString.SplitByLength(printContentText[j], 136).ToArray();
                                    for (int k = 0; k < tmpStringArray.Length; k++)
                                    {
                                        printText = printText + tmpStringArray[k] + "\n";
                                    }
                                }

                                // сделать проверку количества строк, если их больше чем 74, то продумать как разделять richTextBox на страницы
                                // при отладке в windows 2003 на виртуальном xps принтере происходит переполнение если строк больше чем 74
                                break;

                            case -1:
                                MessageBox.Show("Недопустимый индекс в списке тем.");
                                break;

                            default:
                                int i = 0;
                                command = new SQLiteCommand("select question_id, title, text from Questions where Subject=:value1", connect);
                                command.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                                command.Parameters[0].Value = listBox1.SelectedIndex;
                                try
                                {
                                    SQLiteDataReader reader = command.ExecuteReader();
                                    while (reader.Read())
                                    {                                        
                                        i++;
                                        if (i > tabControl1.SelectedIndex)
                                        {
                                            break;
                                        }
                                    }

                                    if (i == 0)
                                    {
                                        MessageBox.Show("Для этой темы еще нет вопросов.");
                                        return;
                                    }

                                    printText = "Вопрос №" + reader[0] + ": ";

                                    tmpStringArray = ExtentionString.SplitByLength(reader[1].ToString(), 124).ToArray();
                                    for (int k = 0; k < tmpStringArray.Length; k++)
                                    {
                                        printText = printText + tmpStringArray[k] + "\n";
                                    }

                                    printText = printText + "\n";

                                    tmpStringArray = ExtentionString.SplitByLength(reader[2].ToString(), 136).ToArray();
                                    for (int k = 0; k < tmpStringArray.Length; k++)
                                    {
                                        printText = printText + tmpStringArray[k] + "\n";
                                    }
                                }
                                catch (System.Data.SQLite.SQLiteException ex)
                                {
                                    MessageBox.Show(ex.Message);
                                }
                                break;
                        }

                        printForm.richTextBox1.Text = printText;
                        printForm.ShowDialog();
                    }                    
                    break;

                default:
                    MessageBox.Show("Неизвестный режим.", "Составление билетов", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
            }
        }

        private void prevToolStripMenuItem_Click(object sender, EventArgs e)
        {
            switch (currentState)
            {
                case 1:
                    panel1.Visible = true;
                   
                    prevToolStripMenuItem.Enabled = false;
                    button1.Visible = false;
                    currentState--;

                    panel2.Visible = false;
                    this.button2.Text = "Далее";
                    tabControl1.TabPages.Clear();
                    break;
                case 2:
                    //currentState--;
                    break;
                default:
                    MessageBox.Show("Неизвестный режим.", "Составление билетов", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
                    break;
            }
        }        

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (listBox1.SelectedIndex)
            {
                case 0:
                    label1.Text = "Нажав далее вы можете отобразить все билеты. Каждый билет включает в себя два теоретических вопроса " +
                              "из разных разделов курса и одну задачу.";
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    label1.Text = "Нажав далее вы можете получить список вопросов с возможностью распечатать его.";
                    break;
                default:
                    label1.Text = "Здесь будет отображаться справочная информация";
                    break;
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 aboutBox1 = new AboutBox1();
            aboutBox1.ShowDialog();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult result = MessageBox.Show("Выйти из программы?", "Составление билетов", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (result != DialogResult.Yes) {
                e.Cancel = true;
            }
        }
    }

    static class ExtentionString
    {
        // переделать для разделения с учетом полного слова
        public static IEnumerable<string> SplitByLength(this string str, int maxLength)
        {
            for (int i = 0; i < str.Length; i += maxLength)
            {
                yield return str.Substring(i, Math.Min(maxLength, str.Length - i));
            }
        }
    }
}