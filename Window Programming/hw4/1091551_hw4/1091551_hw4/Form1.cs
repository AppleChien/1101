using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1091551_hw4
{
    public partial class Form1 : Form
    {
        Color c = Color.Red;
        Random rd = new Random();
        int xplace = 100, yplace = 70;
        int xspeed, yspeed;
        int xposition = 60;
        int count = 1;
        int point = 0;

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.Black, 60, 60, 350, 350);
            e.Graphics.FillEllipse(new SolidBrush(c), xplace, yplace, 10, 10);
            e.Graphics.FillRectangle(new SolidBrush(Color.DeepPink), xposition, 410, 40, 10);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            c = Color.Red;
            toolStripButton1.Checked = true;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = false;
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            c = Color.Green;
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = true;
            toolStripButton3.Checked = false;
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            c = Color.Blue;
            toolStripButton1.Checked = false;
            toolStripButton2.Checked = false;
            toolStripButton3.Checked = true;
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            xposition = e.Location.X;
            if (xposition <= 60) xposition = 60;
            else if (xposition >= 370) xposition = 370;
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (count % 5 == 0)
            {
                if (timer1.Interval > 2) timer1.Interval -= 5;
                if (xspeed > 0) xspeed++;
                else xspeed--;
                if (yspeed > 0) yspeed++;
                else yspeed--;
            }
            toolStripStatusLabel1.Text = Convert.ToString(count++);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            xplace += xspeed;
            yplace += yspeed;

            if (xplace >= 400)
            {
                xplace = 400;
                xspeed *= -1;
            }
            else if (xplace <= 60)
            {
                xplace = 60;
                xspeed *= -1;
            }
            if (yplace <= 60)
            {
                yplace = 60;
                yspeed *= -1;
            }

            if (yplace >= 400)
            {
                if (xplace >= xposition - 2 && xplace <= xposition + 42)
                {
                    //toolStripStatusLabel3.Text = Convert.ToString(++point);
                    yplace = 400;
                    yspeed *= -1;
                }
                else
                {
                    timer1.Stop();
                    timer2.Stop();
                    toolStripStatusLabel2.Text = "Game over";
                }
            }

            Invalidate();
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = "0";
            toolStripStatusLabel2.Text = "Playing";
            //toolStripStatusLabel3.Text = "0";
            xplace = 100;
            yplace = 70;
            xspeed = 3 + rd.Next(7);
            yspeed = 3 + rd.Next(7);
            count = 0;
            point = 0;

            timer1.Interval = 101;
            timer1.Start();
            timer2.Start();
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            toolStripButton1.Checked = true;
            xspeed = 3 + rd.Next(7);
            yspeed = 3 + rd.Next(7);
        }
    }
}
