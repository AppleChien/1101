using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1091551_hw6
{
    public partial class Form1 : Form
    {
        Image[] p = new Image[3];
        Image[] fruit = new Image[3];
        Image bowl = Properties.Resources.Bowl;
        Bitmap[] img = new Bitmap[3];
        Bitmap[] imgClone = new Bitmap[3];

        int np = 0;
        int time = 120;
        int point = 0;
        int xpos = 0;
        int[] fruitx = new int[3];
        int[] fruity = new int[3];

        Random rd = new Random();
        public Form1()
        {
            InitializeComponent();
            DoubleBuffered = true;

        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(imgClone[np], 0, 30, 500, 300);
            e.Graphics.DrawImage(bowl, xpos, 325, 80, bowl.Height);
            e.Graphics.DrawImage(fruit[0], fruitx[0], fruity[0], fruit[0].Width, fruit[0].Height);
            e.Graphics.DrawImage(fruit[1], fruitx[1], fruity[1], fruit[1].Width, fruit[1].Height);
            e.Graphics.DrawImage(fruit[2], fruitx[2], fruity[2], fruit[2].Width, fruit[2].Height);
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            label1.Text = "Remaining: " + --time + " Seconds";

            if (time == 0)
            {
                timer2.Stop();
                timer1.Stop();
            }

            if (time % 10 == 0)
            {
                ++np;
                if (np == 3) np = 0;
                Invalidate();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            fruit[0] = Properties.Resources.Tomato;
            fruit[1] = Properties.Resources.StawBerry;
            fruit[2] = Properties.Resources.Banana;

            p[0] = Properties.Resources.Hydrangeas;
            img[np] = (Bitmap)p[np];
            backImageClone();
            ++np;

            p[1] = Properties.Resources.Penguins;
            img[np] = (Bitmap)p[np];
            backImageClone();
            ++np;

            p[2] = Properties.Resources.Tulips;
            img[np] = (Bitmap)p[np];
            backImageClone();
            ++np;

            if (np == 3) np = 0;

            fruitx[0] = 0;
            fruitx[1] = -100;
            fruitx[0] = -200;
            fruitx[0] = rd.Next(450);
            fruitx[1] = rd.Next(450);
            fruitx[2] = rd.Next(450);

            Invalidate();
        }

        void backImageClone()
        {
            imgClone[np] = (Bitmap)img[np].Clone();
            int x, y;

            for (x = 0; x < imgClone[np].Width; x++)
            {
                for (y = 0; y < imgClone[np].Height; y++)
                {
                    Color pixelColor = imgClone[np].GetPixel(x, y);
                    Color newColor = pixelColor;
                    newColor = Color.FromArgb(pixelColor.A / 2, pixelColor.R, pixelColor.G, pixelColor.B);
                    imgClone[np].SetPixel(x, y, newColor);
                }
            }
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            xpos = e.Location.X;
            if (xpos < 0) xpos = 0;
            else if (xpos > 410) xpos = 410;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            for (int i = 0; i < 3; ++i)
            {
                fruity[i] += 10;

                if (fruity[i] >= 325 && fruitx[i] >= xpos - 3 && fruitx[i] <= xpos + 83)
                {
                    label2.Text = "Recieve: " + ++point;
                    fruity[i] = 0;
                    fruitx[i] = rd.Next(450);
                }
            }

            Invalidate();
        }

        private void restartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            np = 0;
            time = 120;
            point = 0;
            label1.Text = "Remaining: " + time + " Seconds";
            label2.Text = "Recieve: " + point;
            for (int i = 0; i < 3; ++i) fruity[i] = 0;
            Invalidate();
        }
    }
}
