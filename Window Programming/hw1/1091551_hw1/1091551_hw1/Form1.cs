using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1091551_hw1
{
    public partial class Form1 : Form
    {
        Rectangle rect;
        public Form1()
        {
            InitializeComponent();
            rect = new Rectangle();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Size = new Size(300, 300);
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            int r, g, b;
            Random rd = new Random();
            Brush b1;
            Pen p1 = new Pen(Color.Black);
            Rectangle rec;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    r = rd.Next(256);
                    g = rd.Next(256);
                    b = rd.Next(256);
                    b1 = new SolidBrush(Color.FromArgb(r, g, b));
                    rec = new Rectangle(50 * j, 50 * i, 50, 50);
                    e.Graphics.FillRectangle(b1, rec);
                    e.Graphics.DrawRectangle(p1, rec);
                }
            }
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            Rectangle[] rec = new Rectangle[9];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    rec[3 * i + j].X = j * 50;
                    rec[3 * i + j].Y = i * 50;
                    rec[3 * i + j].Height = 50;
                    rec[3 * i + j].Width = 50;
                }
            }

            Brush b1;
            Pen p1 = new Pen(Color.Black);
            int r, g, b;
            Random rd = new Random();

            for (int i = 0; i < 9; i++)
            {
                if (rec[i].Contains(e.Location))
                {
                    Graphics gs = this.CreateGraphics();
                    r = rd.Next(256);
                    g = rd.Next(256);
                    b = rd.Next(256);
                    b1 = new SolidBrush(Color.FromArgb(r, g, b));
                    gs.FillRectangle(b1, rec[i]);
                    gs.DrawRectangle(p1, rec[i]);
                }
            }
        }
    }
    
}
