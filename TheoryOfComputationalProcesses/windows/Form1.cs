using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace compproc
{
    public partial class Form1 : Form
    {
        private int[,] mtrx;
        private Form2 form2 = new Form2();
        private Form3 form3 = new Form3();
        private Form4 form4 = new Form4();
        private String appName = "Преобразование матрицы";
        private String defaultFileName = "Документ1.txt";
        private String currentFileName;
        private int defaultRowCount = 3;
        private int defaultColCount = 3;
        public int maxWidth;
        public int maxHeight;
        public Boolean haveError = false;
        
        public Form1()
        {
            InitializeComponent();
            currentFileName = defaultFileName;
            this.Text = currentFileName + " | " + appName;
            textBox1.Text = defaultRowCount.ToString();
            textBox2.Text = defaultColCount.ToString();
            System.Drawing.Rectangle workingRectangle = Screen.PrimaryScreen.WorkingArea;
            maxWidth = workingRectangle.Width;
            maxHeight = workingRectangle.Height;
            resizeDataGridView();
        }

        public void showSrcForm()
        {
            form3.Show();

            int curWidth = form3.dataGridView1.ColumnCount;
            if (curWidth > (maxWidth / 60)) {
                curWidth = (maxWidth / 60);
            }
            form3.Width = curWidth * 60;

            if ((maxWidth - (this.Left + this.Width)) > form3.Width)
            {
                form3.Left = this.Left + this.Width;
            }            
            else
            {
                form3.Left = this.Left - form3.Width;
            }
            if (((form3.Left + form3.Width) > maxWidth) || (form3.Left < 0))
            {
                form3.Left = 0;
            }
            
            form3.Height = (form3.dataGridView1.Rows.Count + 2) * 22;
            if (form3.Height > maxHeight)
            {
                form3.Height = maxHeight;
            }

            form3.Top = this.Top;
            if ((form3.Top + form3.Height) > maxHeight)
            {
                form3.Top = 0;
            }            
        }

        public void showDstForm()
        {            
            showSrcForm();
            form4.Show();

            int curWidth = form4.dataGridView2.ColumnCount;
            if (curWidth > (maxWidth / 60))
            {
                curWidth = (maxWidth / 60);
            }
            form4.Width = curWidth * 60;

            if ((maxWidth - (form3.Left + form3.Width)) > form4.Width)
            {
                form4.Left = form3.Left + form3.Width;
            }
            else
            {
                form4.Left = form3.Left - form4.Width;
            }
            if (((form4.Left + form4.Width) > maxWidth) || (form4.Left < 0))
            {
                form4.Left = 0;
            }

            form4.Height = (form4.dataGridView2.Rows.Count + 2) * 22;
            if (form4.Height > maxHeight)
            {
                form4.Height = maxHeight;
            }

            form4.Top = this.Top;
            if ((form4.Top + form4.Height) > maxHeight)
            {
                form4.Top = 0;
            }
        }

        public void showMessageForm(Form sender, String message)
        {
            form2.label1.Text = message;
            form2.Show();

            if ((maxWidth - (sender.Left + sender.Width)) > form2.Width)
            {
                form2.Left = sender.Left + sender.Width;
            }
            else
            {
                form2.Left = sender.Left - form2.Width;
            }
            if (((form2.Left + form2.Width) > maxWidth) || (form2.Left < 0))
            {
                form2.Left = 0;
            }

            form2.Top = sender.Top;
            if ((form2.Top + form2.Height) > maxHeight)
            {
                form2.Top = 0;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void loadFromDataGridView()
        {
            int rowCount = form3.dataGridView1.RowCount;
            int colCount = form3.dataGridView1.Columns.Count;
            if (rowCount > 0 && colCount > 0)
            {
                mtrx = new int[rowCount, colCount];
            }
            for (int i = 0; i < rowCount; i++)
            {
                for (int j = 0; j < colCount; j++)
                {
                    if ((form3.dataGridView1.Rows[i].Cells[j].Value != null) &&
                        (form3.dataGridView1.Rows[i].Cells[j].Value != ""))
                    {
                        mtrx[i, j] = Convert.ToInt32(form3.dataGridView1.Rows[i].Cells[j].Value);
                    }
                }
            }
        }

        private void loadToDataGridView()
        {
            for (int i = 0; i < form3.dataGridView1.RowCount; i++)
            {
                for (int j = 0; j < form3.dataGridView1.Columns.Count; j++)
                {
                    form3.dataGridView1.Rows[i].Cells[j].Value = "0";
                }
            }

            int rowCount;
            int colCount;
            try
            {
                rowCount = mtrx.GetLength(0);
                colCount = mtrx.GetLength(1);
            }
            catch (Exception)
            {
                return;
            }
            

            for (int i = 0; i < rowCount; i++)
            {
                for (int j = 0; j < colCount; j++)
                {
                    if ((i < form3.dataGridView1.RowCount) &&
                        (j < form3.dataGridView1.Columns.Count))
                    {
                        form3.dataGridView1.Rows[i].Cells[j].Value = mtrx[i, j].ToString();
                    }
                }
            }
        }

        private void resizeDataGridView()
        {
            loadFromDataGridView();

            int colCount = 0;
            int rowCount = 0;

            if ((textBox1.Text != "" && textBox1.Text != "0") &&
                (textBox2.Text != "" && textBox2.Text != "0"))
            {
                try
                {
                    rowCount = Convert.ToInt32(textBox1.Text);                    
                }
                catch (Exception)
                {
                    // convert error
                    showMessageForm(this, "Недопустимое значение!");
                    textBox1.BackColor = Color.Red;
                    textBox1.ForeColor = Color.White;
                    haveError = true;
                    return;
                }

                try
                {                    
                    colCount = Convert.ToInt32(textBox2.Text);
                }
                catch (Exception)
                {
                    // convert error
                    showMessageForm(this, "Недопустимое значение!");
                    textBox2.BackColor = Color.Red;
                    textBox2.ForeColor = Color.White;
                    haveError = true;
                    return;
                }
            }

            if (form3.dataGridView1.Columns.Count > 1)
            {
                int oldColCount = form3.dataGridView1.Columns.Count;
                for (int i = 1; i < oldColCount; i++)
                {
                    form3.dataGridView1.Columns.RemoveAt(oldColCount - i);
                }
            }
            form3.dataGridView1.Rows.Clear();

            for (int i = 0; i < rowCount; i++)
            {
                form3.dataGridView1.Rows.Add("");
            }
            for (int j = 1; j < colCount; j++)
            {
                DataGridViewColumn col = (DataGridViewColumn)form3.dataGridView1.Columns[0].Clone();
                form3.dataGridView1.Columns.Add(col);
            }

            loadToDataGridView();
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!haveError)
            {
                form2.Visible = false;

                OpenFileDialog openFileDialog1 = new OpenFileDialog();
                openFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                openFileDialog1.FilterIndex = 2;
                openFileDialog1.RestoreDirectory = true;

                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    String input = File.ReadAllText(openFileDialog1.FileName);
                    currentFileName = openFileDialog1.SafeFileName;
                    this.Text = currentFileName + " | " + appName;
                    int i = 0, j = 0;
                    foreach (var row in input.Split('\n'))
                    {
                        j = 0;
                        foreach (var col in row.Trim().Split(' '))
                        {
                            try
                            {
                                int temp = int.Parse(col.Trim());
                            }
                            catch (Exception)
                            {
                                showMessageForm(this, "Неверный формат матрицы.");
                                return;
                            }
                            j++;
                        }
                        i++;
                    }
                    textBox1.Text = i.ToString();
                    textBox2.Text = j.ToString();
                    resizeDataGridView();

                    i = 0;
                    j = 0;
                    foreach (var row in input.Split('\n'))
                    {
                        j = 0;
                        foreach (var col in row.Trim().Split(' '))
                        {
                            form3.dataGridView1.Rows[i].Cells[j].Value = int.Parse(col.Trim()).ToString();
                            j++;
                        }
                        i++;
                    }
                    showSrcForm();
                }
            }
        }        

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!haveError)
            {
                form2.Visible = false;

                if (form3.dataGridView1.RowCount < 1)
                {
                    showMessageForm(this, "Сначала создайте матрицу.");
                    return;
                }

                for (int i = 0; i < form3.dataGridView1.RowCount; i++)
                {
                    for (int j = 0; j < form3.dataGridView1.Columns.Count; j++)
                    {
                        form3.dataGridView1.Rows[i].Cells[j].Style.BackColor = SystemColors.Window;
                        form3.dataGridView1.Rows[i].Cells[j].Style.ForeColor = SystemColors.WindowText;
                        haveError = false;

                        try
                        {
                            int tmp = Convert.ToInt32(form3.dataGridView1.Rows[i].Cells[j].Value.ToString());
                        }
                        catch (Exception)
                        {
                            showMessageForm(form3, "Недопустимое значение!");
                            showSrcForm();
                            form3.dataGridView1.Rows[i].Cells[j].Style.BackColor = Color.Red;
                            form3.dataGridView1.Rows[i].Cells[j].Style.ForeColor = Color.White;
                            haveError = true;
                            return;
                        }

                        /*if (form3.dataGridView1.Rows[i].Cells[j].Value == null)
                        {
                            showMessageForm(this, "Заполнены не все поля матрицы.");
                            return;
                        }*/
                    }
                }

                StreamWriter tw;
                SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                saveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                saveFileDialog1.FilterIndex = 2;
                saveFileDialog1.RestoreDirectory = true;
                saveFileDialog1.FileName = currentFileName;

                if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    using (tw = new StreamWriter(saveFileDialog1.OpenFile()))
                    {
                        for (int i = 0; i < form3.dataGridView1.RowCount; i++)
                        {
                            for (int j = 0; j < form3.dataGridView1.Columns.Count; j++)
                            {
                                if (j != 0)
                                {
                                    tw.Write(" ");
                                }

                                tw.Write(form3.dataGridView1.Rows[i].Cells[j].Value);
                            }
                            if ((i + 1) != form3.dataGridView1.RowCount)
                            {
                                tw.WriteLine();
                            }
                        }
                    }
                }
            }
        }

        private int computeColCharacteristic(int[,] mt, int col, int rowCount)
        {
            int sum = 0;
            for (int i = 0; i < rowCount; i++)
            {
                if ((mt[i, col] < 0) && ((mt[i, col] % 2) != 0))
                {
                    sum += Math.Abs(mt[i, col]);
                }
            }
            return sum;
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
                form2.Visible = false;

                int rowCount = form3.dataGridView1.RowCount;
                int colCount = form3.dataGridView1.Columns.Count;
                int[,] mt = new int[rowCount, colCount];
                int tmp;
                int[] srtLst = new int[colCount];

                for (int i = 0; i < rowCount; i++)
                {
                    for (int j = 0; j < colCount; j++)
                    {
                        form3.dataGridView1.Rows[i].Cells[j].Style.BackColor = SystemColors.Window;
                        form3.dataGridView1.Rows[i].Cells[j].Style.ForeColor = SystemColors.WindowText;
                        haveError = false;

                        try
                        {
                            mt[i, j] = Convert.ToInt32(form3.dataGridView1.Rows[i].Cells[j].Value.ToString());
                        }
                        catch (Exception)
                        {
                            showMessageForm(form3, "Недопустимое значение!");
                            showSrcForm();
                            form3.dataGridView1.Rows[i].Cells[j].Style.BackColor = Color.Red;
                            form3.dataGridView1.Rows[i].Cells[j].Style.ForeColor = Color.White;
                            haveError = true;
                            return;
                        }
                    }
                }

                for (int i = 0; i < colCount; i++)
                {
                    srtLst[i] = computeColCharacteristic(mt, i, rowCount);
                }

                for (int i = 0; i < colCount; i++)
                {
                    for (int j = colCount - 1; j > i; j--)
                    {
                        if (srtLst[j - 1] > srtLst[j])
                        {
                            tmp = srtLst[j - 1];
                            srtLst[j - 1] = srtLst[j];
                            srtLst[j] = tmp;

                            for (int k = 0; k < rowCount; k++)
                            {
                                tmp = mt[k, j - 1];
                                mt[k, j - 1] = mt[k, j];
                                mt[k, j] = tmp;
                            }
                        }
                    }
                }

                if (form4.dataGridView2.Columns.Count > 1)
                {
                    int oldColCount = form4.dataGridView2.Columns.Count;
                    for (int i = 1; i < oldColCount; i++)
                    {
                        form4.dataGridView2.Columns.RemoveAt(oldColCount - i);
                    }
                }
                form4.dataGridView2.Rows.Clear();

                for (int i = 0; i < rowCount; i++)
                {
                    form4.dataGridView2.Rows.Add("");
                }
                for (int j = 1; j < colCount; j++)
                {
                    DataGridViewColumn col = (DataGridViewColumn)form4.dataGridView2.Columns[0].Clone();
                    form4.dataGridView2.Columns.Add(col);
                }

                for (int i = 0; i < rowCount; i++)
                {
                    for (int j = 0; j < colCount; j++)
                    {
                        form4.dataGridView2.Rows[i].Cells[j].Value = mt[i, j].ToString();
                    }
                }

                showDstForm();
        }


        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (!haveError)
            {
                resizeDataGridView();
                showSrcForm();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text.Length < 3)
            {
                form2.Visible = false;
                textBox1.BackColor = SystemColors.Window;
                textBox1.ForeColor = SystemColors.WindowText;
                haveError = false;
            }
            else
            {
                showMessageForm(this, "Превышено максимальное значение!");
                textBox1.BackColor = Color.Red;
                textBox1.ForeColor = Color.White;
                haveError = true;
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            if (textBox2.Text.Length < 3)
            {
                form2.Visible = false;
                textBox2.BackColor = SystemColors.Window;
                textBox2.ForeColor = SystemColors.WindowText;
                haveError = false;
            }
            else
            {
                showMessageForm(this, "Превышено максимальное значение!");
                textBox2.BackColor = Color.Red;
                textBox2.ForeColor = Color.White;
                haveError = true;
            }
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 aboutBox1 = new AboutBox1();
            aboutBox1.Show();
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            showSrcForm();
        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            showDstForm();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                int tmp = Convert.ToInt32(textBox1.Text);
                form2.Visible = false;
                textBox1.BackColor = SystemColors.Window;
                textBox1.ForeColor = SystemColors.WindowText;
                haveError = false;
            }
            catch (Exception)
            {
                //
            }

            try
            {
                int tmp = Convert.ToInt32(textBox2.Text);
                form2.Visible = false;
                textBox2.BackColor = SystemColors.Window;
                textBox2.ForeColor = SystemColors.WindowText;
                haveError = false;
            }
            catch (Exception)
            {
                //
            }

            resizeDataGridView();
            //showSrcForm();
        }
    }
}
