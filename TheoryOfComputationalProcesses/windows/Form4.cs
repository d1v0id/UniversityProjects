using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace compproc
{
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }

        private void Form4_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void dataGridView2_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                int tmp = Convert.ToInt32(dataGridView2.CurrentCell.Value.ToString());
                Form form2 = Application.OpenForms["Form2"];
                form2.Visible = false;
                dataGridView2.CurrentCell.Style.BackColor = SystemColors.Window;
                dataGridView2.CurrentCell.Style.ForeColor = SystemColors.WindowText;
            }
            catch (Exception)
            {
                //
            }
        }
    }
}
