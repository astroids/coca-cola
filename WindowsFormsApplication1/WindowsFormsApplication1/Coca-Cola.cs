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
using System.Drawing.Imaging;
using System.Diagnostics;
using System.Runtime.InteropServices;


/*
TO DO LIST

 * 1)fix handles
 * 2)write in ASM
 * 3)start second algorithms if above works 
 * 
 * 
 * NON IMPORTANT STUFF
 * 1)reset trackbar after every pic load
 * 2)text format
 * 3)del unused funs







*/
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// lock bitse bak http://msdn.microsoft.com/en-us/library/ms229672.aspx
        /// unmanaged buffer
        /// </summary>
        public Bitmap bmpFront;
        public byte[] Original;
        private static Int32 imagesize = 0;
        public static Rectangle picRect;
        public BitmapData bitdata;


        Stopwatch stopCsharp = new Stopwatch();



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
                        // COPY ATM CHANGE TO HANDLE
                        bmpFront = (Bitmap)Image.FromFile(asd.FileName);
                        SaveOriginal(bmpFront);

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

        public void clearImage()
        {
            if (Original != null)
            {
                Original = null;
            }
        }




        //bu c++ move olabilir
        public void SaveOriginal(Bitmap source)
        {                            
            clearImage();
            imagesize = source.Width * source.Height * 3;
            Original = new byte[imagesize];

            //lock bits and stuff
            picRect.Width = source.Width;
            picRect.Height = source.Height;

            //SON DEGERI MMX E  UYMAZSA DEGISTIRMEYI DENE
            bitdata = source.LockBits(picRect,ImageLockMode.ReadOnly,PixelFormat.Format24bppRgb);
            unsafe
            {
                byte* p = (byte*)bitdata.Scan0.ToPointer();
            
                for (int i = 0; i < imagesize; i++)
                {
                    Original[i] = *p++;
                }
            }
            source.UnlockBits(bitdata);
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

        
        
         [DllImport("search.dll")] static unsafe extern void adjustb(byte* sour,short bar,Int32 imgSize,byte* orig);
                      
        
        /// <summary>
        /// adjustb   olcak  bu dll c adi
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
       

        private void trackASM_Scroll(object sender, EventArgs e)
        {
            bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            //simdiden zaman tutmaca

           
            stopCsharp.Start();
            unsafe
            {

                //yukariyida fixlememiz gerekiyo glba
                fixed (byte* or = Original )
                {

                //    adjustb((byte*)bitdata.Scan0.ToPointer(), (short)trackASM.Value, imagesize, or);                          //  FIX AFTER DEBUG

                    //adjustb((byte*)bitdata.Scan0.ToPointer(), (short)60, imagesize, or);  
                  
                    byte* norm = (byte*)bitdata.Scan0.ToPointer();
                       int size = imagesize;
                        short bar = (short)trackASM.Value;
                        for (int i = 0; i < size; i++)
                        {
                            if ((short)or[i] + bar < 0)
                            {
                                norm[i] = 0;
                            }
                            else if ((short)or[i] + bar > 255)
                            {
                                norm[i] = 255;
                            }
                            else
                            {
                                 norm[i] = (byte)(or[i] + bar);         //duzelt olmazsa rollback
                            }

                        
                    }
                    
                    
                }

            }
            stopCsharp.Stop();
            labelCPP.Text = stopCsharp.Elapsed.ToString();
            stopCsharp.Reset();
            pic.Image = bmpFront;
                
            bmpFront.UnlockBits(bitdata);

        }

        private void pic_Click(object sender, EventArgs e)
        {

        }


    }
}
