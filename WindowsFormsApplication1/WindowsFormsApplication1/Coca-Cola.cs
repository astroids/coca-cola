using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Bitmap bmpFront;
        public Form1()
        {
            InitializeComponent();
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void labelCPP_Click(object sender, EventArgs e)
        {

        }

        private void exitToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void openToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            OpenFileDialog asd = new OpenFileDialog();
            if (asd.ShowDialog() == DialogResult.OK)        //file dialog acildi eger secerse bi resim
            {
                try
                {
                   
                    {
                        // load image to bitmap handle
                       // bmpFront = new Bitmap(new MemoryStream(Image.FromFile(asd.))).GetHbitmap();
                        bmpFront = (Bitmap)Image.FromFile(asd.FileName);
                        //MessageBox.Show("Not implemanted yet");

                        pic.Image = bmpFront;
                        trackASM.Enabled = true;
                    }
                }
                catch (Exception)
                {

                    MessageBox.Show("File Coulnt't be opend");
                }
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }


    }
}
