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
    public partial class Form3 : Form
    {
        private int questionsCount;
        private int answersCount;
        private int answersTotalCount;
        private String[] answersContent; 
        public bool modify;
        public int newQuestionNumber;
        private SQLiteConnection connect;

        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            connect = new SQLiteConnection("Data Source=TestCreater.db");
            connect.Open();
        }        

        private void Form3_Shown(object sender, EventArgs e)
        {
            SQLiteCommand command1;
            SQLiteDataReader reader1;
            string sqlQuery1;

            sqlQuery1 = "select count(question_id) from Questions";
            command1 = new SQLiteCommand(sqlQuery1, connect);
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

            sqlQuery1 = "select count(answer_id) from Answers";
            command1 = new SQLiteCommand(sqlQuery1, connect);
            try
            {
                reader1 = command1.ExecuteReader();
                reader1.Read();
                answersTotalCount = Convert.ToInt32(reader1[0]);
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }

            sqlQuery1 = "select question_id from Questions order by question_id";
            command1 = new SQLiteCommand(sqlQuery1, connect);
            try
            {
                reader1 = command1.ExecuteReader();
                while (reader1.Read())
                {
                    listBox1.Items.Add(reader1[0]);
                }

                if (listBox1.Items.Count > 0)
                {
                    listBox1.SelectedIndex = 0;
                    updateTestPreview();
                }

                modify = false;
                newQuestionNumber = 0;
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void updateTestPreview()
        {
            SQLiteCommand command1, command2;
            SQLiteDataReader reader1;
            SQLiteDataReader reader2;
            string sqlQuery1, sqlQuery2;
            int j;

            richTextBox2.Text = "";

            sqlQuery1 = "select count(question_id) from Questions";
            command1 = new SQLiteCommand(sqlQuery1, connect);
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

            for (int i = 0; i < listBox1.Items.Count; i++)
            {
                sqlQuery1 = "select question_id, qtext from Questions where question_id=" + listBox1.Items[i];
                command1 = new SQLiteCommand(sqlQuery1, connect);
                try
                {
                    reader1 = command1.ExecuteReader();

                    if (reader1.Read())
                    {
                        richTextBox2.Text = richTextBox2.Text + listBox1.Items[i] + ") " + reader1[1] + "\n";

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
                            richTextBox2.Text += "           " + char.ConvertFromUtf32(1040 + j);
                            richTextBox2.Text += ") " + answersContent[j].ToString();

                            if ((j % 2) != 0)
                            {
                                richTextBox2.Text += "\n";
                            }
                        }

                        richTextBox2.Text += "\n";
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!modify)
            {
                SQLiteCommand command1, command2;
                string sqlQuery1, sqlQuery2;
                int j;

                listBox2.Items.Clear();
                button2.Enabled = true;
                button3.Enabled = true;
                richTextBox1.Enabled = true;
                listBox2.Enabled = true;

                SQLiteDataReader reader1;
                SQLiteDataReader reader2;

                sqlQuery1 = "select question_id, qtext, right_answer from Questions where question_id=:value1";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                command1.Parameters[0].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);

                try
                {
                    reader1 = command1.ExecuteReader();

                    if (reader1.Read())
                    {
                        richTextBox1.Text = reader1[1].ToString();

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
                            listBox2.Items.Add(answersContent[j].ToString());
                        }
                        numericUpDown1.Minimum = 1;
                        numericUpDown1.Maximum = Convert.ToInt32(answersCount);
                        if (Convert.ToInt32(reader1[2]) <= numericUpDown1.Maximum)
                        {
                            numericUpDown1.Value = Convert.ToInt32(reader1[2]);
                        }
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (modify)
            {
                modify = false;
                listBox1.Enabled = true;
                button4.Enabled = true;
                updateTestPreview();
            }
            else
            {
                Close();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int lastQuestionNumber = 0;

            SQLiteCommand command1;
            SQLiteDataReader reader1;
            string sqlQuery1;

            sqlQuery1 = "select max(question_id) from Questions";
            command1 = new SQLiteCommand(sqlQuery1, connect);
            try
            {
                reader1 = command1.ExecuteReader();
                reader1.Read();
                if (reader1[0].ToString() != "")
                {
                    lastQuestionNumber = Convert.ToInt32(reader1[0]);
                }
            }
            catch (System.Data.SQLite.SQLiteException ex)
            {
                MessageBox.Show(ex.Message);
            }

            listBox1.Items.Add(lastQuestionNumber + 1);
            richTextBox1.Text = "";
            richTextBox2.Text = "";
            listBox2.Items.Clear();
            numericUpDown1.Minimum = 0;
            numericUpDown1.Maximum = 0;
            numericUpDown1.Value = 0;
            listBox1.SelectedIndex = listBox1.Items.Count - 1;
            listBox1.Enabled = false;
            button4.Enabled = false;
            modify = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form4 answerForm = new Form4();
            answerForm.ShowDialog(this);
        }

        private void createNewQuestion()
        {
            SQLiteCommand command1;
            string sqlQuery1;

            if ((richTextBox1.Text.CompareTo("") != 0) && (numericUpDown1.Value != 0) && (listBox2.Items.Count > 2))
            {
                questionsCount++;

                int currentQuestionNumber = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);

                for (int i = 0; i < listBox2.Items.Count; i++)
                {
                    sqlQuery1 = "insert into Answers values(:value1, :value2, :value3)";
                    command1 = new SQLiteCommand(sqlQuery1, connect);
                    command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                    command1.Parameters.Add(new SQLiteParameter("value2", DbType.Int32));
                    command1.Parameters.Add(new SQLiteParameter("value3", DbType.String));

                    answersTotalCount++;
                    command1.Parameters[0].Value = answersTotalCount;
                    
                    command1.Parameters[1].Value = currentQuestionNumber;

                    command1.Parameters[2].Value = listBox2.Items[i];

                    try
                    {
                        command1.ExecuteNonQuery(); // Ответ добавлен в БД
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }

                sqlQuery1 = "insert into Questions values(:value1, '', :value2, 0, :value3)";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                command1.Parameters.Add(new SQLiteParameter("value2", DbType.String));
                command1.Parameters.Add(new SQLiteParameter("value3", DbType.Int32));
                command1.Parameters[0].Value = currentQuestionNumber;
                command1.Parameters[1].Value = richTextBox1.Text;
                command1.Parameters[2].Value = numericUpDown1.Value;
                try
                {
                    if (command1.ExecuteNonQuery() == 1)
                    {
                        MessageBox.Show("Вопрос добавлен в БД.");

                        modify = false;
                        listBox1.Enabled = true;
                        button4.Enabled = true;
                        updateTestPreview();
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Не все поля заполнены корректно.");
            }
        }

        private void saveCurrentQuestion()
        {
            SQLiteCommand command1;
            string sqlQuery1;

            if ((richTextBox1.Text.CompareTo("") != 0) && (numericUpDown1.Value != 0) && (listBox2.Items.Count > 2))
            {
                sqlQuery1 = "update Answers set question_id=0 where question_id=:value1";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                command1.Parameters[0].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                try
                {
                    if (command1.ExecuteNonQuery() == 1)
                    {
                        MessageBox.Show("Ответы в БД помечены на удаление.");
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }

                for (int i = 0; i < listBox2.Items.Count; i++)
                {
                    sqlQuery1 = "insert into Answers values(:value1, :value2, :value3)";
                    command1 = new SQLiteCommand(sqlQuery1, connect);
                    command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                    command1.Parameters.Add(new SQLiteParameter("value2", DbType.Int32));
                    command1.Parameters.Add(new SQLiteParameter("value3", DbType.String));

                    answersTotalCount++;
                    command1.Parameters[0].Value = answersTotalCount;
                    command1.Parameters[1].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                    command1.Parameters[2].Value = listBox2.Items[i];

                    try
                    {
                        command1.ExecuteNonQuery(); // Ответ добавлен в БД
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }

                sqlQuery1 = "update Questions set qtext=:value1, right_answer=:value2 where question_id=:value3";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.String));
                command1.Parameters.Add(new SQLiteParameter("value2", DbType.Int32));
                command1.Parameters.Add(new SQLiteParameter("value3", DbType.Int32));
                command1.Parameters[0].Value = richTextBox1.Text;
                command1.Parameters[1].Value = numericUpDown1.Value;
                command1.Parameters[2].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                try
                {
                    if (command1.ExecuteNonQuery() == 1)
                    {
                        MessageBox.Show("Вопрос в БД обновлен.");
                        updateTestPreview();
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                MessageBox.Show("Заполнены не все поля.");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (modify.Equals(true))
            {
                createNewQuestion();
            }
            else
            {
                saveCurrentQuestion();
            }
        }

        private void modifyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedIndex > -1)
            {
                Form4 answerForm = new Form4();
                answerForm.modify = true;
                answerForm.textBox1.Text = listBox2.Items[listBox2.SelectedIndex].ToString();
                answerForm.ShowDialog(this);
            }
        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedIndex > -1)
            {
                listBox2.Items.RemoveAt(listBox2.SelectedIndex);
                numericUpDown1.Maximum -= 1;
            }
        }

        private void upToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedIndex > 0)
            {
                String tmp;
                tmp = listBox2.Items[listBox2.SelectedIndex].ToString();
                listBox2.Items[listBox2.SelectedIndex] = listBox2.Items[listBox2.SelectedIndex - 1];
                listBox2.Items[listBox2.SelectedIndex - 1] = tmp;
                listBox2.SelectedIndex = listBox2.SelectedIndex - 1;
            }
        }

        private void downToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox2.SelectedIndex < listBox2.Items.Count - 1)
            {
                String tmp;
                tmp = listBox2.Items[listBox2.SelectedIndex].ToString();
                listBox2.Items[listBox2.SelectedIndex] = listBox2.Items[listBox2.SelectedIndex + 1];
                listBox2.Items[listBox2.SelectedIndex + 1] = tmp;
                listBox2.SelectedIndex = listBox2.SelectedIndex + 1;
            }
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (modify)
            {
                e.Cancel = true;
                MessageBox.Show("Сначала сохраните изменения.");
            }
        }

        private void upToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex > 0)
            {
                modify = true;
                String tmp;
                tmp = listBox1.Items[listBox1.SelectedIndex].ToString();
                listBox1.Items[listBox1.SelectedIndex] = listBox1.Items[listBox1.SelectedIndex - 1];
                listBox1.Items[listBox1.SelectedIndex - 1] = tmp;
                listBox1.SelectedIndex = listBox1.SelectedIndex - 1;
                modify = false;
                updateTestPreview();
            }
        }

        private void downToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex < listBox1.Items.Count - 1)
            {
                modify = true;
                String tmp;
                tmp = listBox1.Items[listBox1.SelectedIndex].ToString();
                listBox1.Items[listBox1.SelectedIndex] = listBox1.Items[listBox1.SelectedIndex + 1];
                listBox1.Items[listBox1.SelectedIndex + 1] = tmp;
                listBox1.SelectedIndex = listBox1.SelectedIndex + 1;
                modify = false;
                updateTestPreview();
            }
        }

        private void deleteToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex > -1)
            {
                SQLiteCommand command1;
                string sqlQuery1;

                modify = true;

                sqlQuery1 = "update Answers set question_id=0 where question_id=:value1";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                command1.Parameters[0].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                try
                {
                    if (command1.ExecuteNonQuery() == 1)
                    {
                        MessageBox.Show("Ответы в БД помечены на удаление.");
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }

                sqlQuery1 = "delete from Questions where question_id=:value1";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                command1.Parameters[0].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                try
                {
                    if (command1.ExecuteNonQuery() == 1)
                    {
                        MessageBox.Show("Вопрос в БД удален.");
                        listBox1.Items.RemoveAt(listBox1.SelectedIndex);
                        listBox1.SelectedIndex = -1;
                        richTextBox1.Text = "";
                        listBox2.Items.Clear();
                        numericUpDown1.Minimum = 0;
                        numericUpDown1.Maximum = 0;
                        numericUpDown1.Value = 0;
                        button2.Enabled = false;
                        button3.Enabled = false;
                        richTextBox1.Enabled = false;
                        listBox2.Enabled = false;
                        updateTestPreview();
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }

                modify = false;
            }
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            if (!modify)
            {                
                Form5 rightAnswersForm = new Form5();

                SQLiteCommand command1, command2;
                SQLiteDataReader reader1;
                SQLiteDataReader reader2;
                string sqlQuery1, sqlQuery2;
                int j;

                rightAnswersForm.richTextBox1.Text = "";

                sqlQuery1 = "select count(question_id) from Questions";
                command1 = new SQLiteCommand(sqlQuery1, connect);
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

                for (int i = 0; i < listBox1.Items.Count; i++)
                {
                    sqlQuery1 = "select question_id, qtext, right_answer from Questions where question_id=" + listBox1.Items[i];
                    command1 = new SQLiteCommand(sqlQuery1, connect);
                    try
                    {
                        reader1 = command1.ExecuteReader();

                        if (reader1.Read())
                        {
                            rightAnswersForm.richTextBox1.Text = rightAnswersForm.richTextBox1.Text + listBox1.Items[i] + ") " + reader1[1] + "\n";                            

                            sqlQuery2 = "select answer_id, atext from Answers where question_id = " + reader1[0] + " order by answer_id";
                            command2 = new SQLiteCommand(sqlQuery2, connect);
                            try
                            {
                                reader2 = command2.ExecuteReader();
                                j = 0;
                                while (reader2.Read())
                                {
                                    j++;
                                    if (j == Convert.ToInt32(reader1[2]))
                                    {
                                        break;
                                    }
                                }
                                rightAnswersForm.richTextBox1.Text += "           " + char.ConvertFromUtf32(1040 + j - 1);
                                rightAnswersForm.richTextBox1.Text += ") " + reader2[1].ToString();
                            }
                            catch (System.Data.SQLite.SQLiteException ex)
                            {
                                MessageBox.Show(ex.Message);
                            }

                            rightAnswersForm.richTextBox1.Text += "\n\n";
                        }
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }

                rightAnswersForm.ShowDialog();
            }
        }

        private void changeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex > -1)
            {
                modify = true;

                SQLiteCommand command1;
                SQLiteDataReader reader1;
                string sqlQuery1;

                Form4 questionForm = new Form4();
                questionForm.Text = "Номер вопроса";
                questionForm.isQuestion = true;
                questionForm.ShowDialog(this);

                sqlQuery1 = "select count(*) from Questions where question_id=:value1";
                command1 = new SQLiteCommand(sqlQuery1, connect);
                command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                command1.Parameters[0].Value = newQuestionNumber;
                try
                {
                    reader1 = command1.ExecuteReader();
                    reader1.Read();
                    if (reader1[0].ToString() != "0")
                    {
                        modify = false;
                        MessageBox.Show("Вопрос с таким номером уже есть.");
                        return;
                    }
                }
                catch (System.Data.SQLite.SQLiteException ex)
                {
                    MessageBox.Show(ex.Message);
                }

                if ((listBox1.SelectedIndex > -1) && (newQuestionNumber > 0))
                {
                    sqlQuery1 = "update Answers set question_id=:value1 where question_id=:value2";
                    command1 = new SQLiteCommand(sqlQuery1, connect);
                    command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                    command1.Parameters.Add(new SQLiteParameter("value2", DbType.Int32));
                    command1.Parameters[0].Value = newQuestionNumber;
                    command1.Parameters[1].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                    try
                    {
                        if (command1.ExecuteNonQuery() == 1)
                        {
                            MessageBox.Show("Номер вопроса в ответах изменен.");
                        }
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }

                    sqlQuery1 = "update Questions set question_id=:value1 where question_id=:value2";
                    command1 = new SQLiteCommand(sqlQuery1, connect);
                    command1.Parameters.Add(new SQLiteParameter("value1", DbType.Int32));
                    command1.Parameters.Add(new SQLiteParameter("value2", DbType.Int32));
                    command1.Parameters[0].Value = newQuestionNumber;
                    command1.Parameters[1].Value = Convert.ToInt32(listBox1.Items[listBox1.SelectedIndex]);
                    try
                    {
                        if (command1.ExecuteNonQuery() == 1)
                        {
                            MessageBox.Show("Номер вопроса в БД изменен.");
                            listBox1.Items[listBox1.SelectedIndex] = newQuestionNumber.ToString();
                            updateTestPreview();
                        }
                    }
                    catch (System.Data.SQLite.SQLiteException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }
                else
                {
                    MessageBox.Show("Недопустимый номер вопроса.");
                }

                modify = false;
            }
        }
    }
}
