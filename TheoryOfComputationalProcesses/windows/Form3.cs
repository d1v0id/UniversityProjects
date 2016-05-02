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
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
        }

        private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            //e.FormattingApplied = true;
            //dataGridView1.CommitEdit(DataGridViewDataErrorContexts.Commit);

            /*try
            {
                int tmp = Convert.ToInt32(dataGridView1.CurrentCell.Value.ToString());
                Form form2 = Application.OpenForms["Form2"];
                form2.Visible = false;
                dataGridView1.CurrentCell.Style.BackColor = SystemColors.Window;
                dataGridView1.CurrentCell.Style.ForeColor = SystemColors.WindowText;
            }
            catch (Exception)
            {                
                //
            }*/
        }
    }
}
