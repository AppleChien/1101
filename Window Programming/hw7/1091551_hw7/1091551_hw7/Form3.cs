using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1091551_hw7
{
    public partial class Form3 : Form
    {
        private double R, G, B, A;

        public Form3()
        {
            InitializeComponent();
        }

        public double getR()
        {
            return R;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            R = (double)trackBar1.Value / 10;
            G = (double)trackBar2.Value / 10;
            B = (double)trackBar3.Value / 10;
            A = (double)trackBar4.Value / 10;
            Close();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label5.Text = "" + (double)trackBar1.Value / 10;
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label6.Text = "" + (double)trackBar2.Value / 10;
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            label7.Text = "" + (double)trackBar3.Value / 10;
        }

        private void trackBar4_Scroll(object sender, EventArgs e)
        {
            label8.Text = "" + (double)trackBar4.Value / 10;
        }

        public double getG()
        {
            return G;
        }

        public double getB()
        {
            return B;
        }

        public double getA()
        {
            return A;
        }
    }
}
