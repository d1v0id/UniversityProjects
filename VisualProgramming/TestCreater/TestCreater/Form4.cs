using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TestCreater
{
    public partial class Form4 : Form
    {
        public Boolean modify = false;
        public Boolean isQuestion = false;

        public Form4()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form3 createForm = (Form3)this.Owner;            

            if (isQuestion)
            {
                createForm.newQuestionNumber = Convert.ToInt32(textBox1.Text);
            }
            else
            {
                if (!modify)
                {
                    createForm.listBox2.Items.Add(textBox1.Text);
                    createForm.numericUpDown1.Minimum = 1;
                    createForm.numericUpDown1.Maximum = createForm.listBox2.Items.Count;
                }
                else
                {
                    createForm.listBox2.Items[createForm.listBox2.SelectedIndex] = textBox1.Text;
                }
            }

            Close();
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (isQuestion)
            {
                if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
                {
                    e.Handled = true;
                }
            }
        }
    }
}
