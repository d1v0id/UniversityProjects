using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SQLite;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TestCreater
{
    public partial class Form2 : Form
    {
        private SQLiteConnection connect;
        private int questionsCount;
        private int answersCount;
        private int[] rightAnswers;
        private String[] answersContent; 

        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            connect = new SQLiteConnection("Data Source=TestCreater.db");
            connect.Open();
        }

        private void Form2_Shown(object sender, EventArgs e)
        {
            SQLiteCommand command1, command2;
            string sqlQuery1, sqlQuery2;
            int i, j;

            sqlQuery1 = "select count(question_id) from Questions";
            command1 = new SQLiteCommand(sqlQuery1, connect);

            SQLiteDataReader reader1;
            SQLiteDataReader reader2;

            try
            {
                reader1 = command1.ExecuteReader();
                reader1.Read();
                questionsCount = Convert.ToInt32(reader1[0]);
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }
            rightAnswers = new int[questionsCount];

            sqlQuery1 = "select question_id, qtext, right_answer from Questions order by random()";
            command1 = new SQLiteCommand(sqlQuery1, connect);            
            try
            {
                reader1 = command1.ExecuteReader();                

                i = 0;
                while (reader1.Read())
                {
                    richTextBox1.Text = richTextBox1.Text + (i + 1) + ") " + reader1[1] + "\n";

                    sqlQuery2 = "select count(answer_id) from Answers where question_id = " + reader1[0];
                    command2 = new SQLiteCommand(sqlQuery2, connect);
                    try
                    {
                        reader2 = command2.ExecuteReader();
                        reader2.Read();
                        answersCount = Convert.ToInt32(reader2[0]);                        
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                    answersContent = new String[answersCount];

                    sqlQuery2 = "select answer_id, atext from Answers where question_id = " + reader1[0] + " order by answer_id";
                    command2 = new SQLiteCommand(sqlQuery2, connect);
                    try
                    {
                        reader2 = command2.ExecuteReader();
                        j = 0;
                        while (reader2.Read())
                        {
                            answersContent[j] = reader2[1].ToString();
                            j++;
                        }
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }

                    for (j = 0; j < answersCount; j++)
                    {
                        // 1040 eq А in russian
                        richTextBox1.Text += "           " + char.ConvertFromUtf32(1040 + j);
                        richTextBox1.Text += ") " + answersContent[j].ToString();

                        if ((j % 2) != 0)
                        {
                            richTextBox1.Text += "\n";
                        }
                    }
                    richTextBox1.Text += "\n";
                        
                    rightAnswers[i] = Convert.ToInt32(reader1[2]);
                    i++;
                }
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            label1.Text = "Правильные ответы: ";
            if (richTextBox1.Text.CompareTo("") != 0) {
                for (int i = 0; i < questionsCount; i++)
                {
                    label1.Text = label1.Text + (i + 1) + ") " +
                        rightAnswers[i].ToString() + "  ";
                }
            }
        }
    }
}
