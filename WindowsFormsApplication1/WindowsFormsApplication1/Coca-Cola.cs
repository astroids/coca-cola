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
//using System.Drawing;
using System.Drawing.Imaging;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

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
        Stopwatch stopCPP = new Stopwatch();
        Stopwatch stopASM = new Stopwatch();

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

        private void labelCS_Click(object sender, EventArgs e)
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
                        trackCS.Enabled = true;
                        trackCPP.Enabled = true;
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

        
        
                      
        
        /// <summary>
        /// adjustb   olcak  bu dll c adi
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
       

        private void trackCS_Scroll(object sender, EventArgs e)
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
                        short bar = (short)trackCS.Value;
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
            labelCS.Text = stopCsharp.ElapsedTicks.ToString();
            stopCsharp.Reset();
            pic.Image = bmpFront;
                
            bmpFront.UnlockBits(bitdata);

        }

        private void pic_Click(object sender, EventArgs e)
        {

        }

        [DllImport("mehlib.dll")]
        static unsafe extern void adjustb(byte* sour, short bar, Int32 imgSize, byte* orig);

        private void trackCPP_Scroll(object sender, EventArgs e)
        {
            bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            stopCPP.Start();
            unsafe
            {
                fixed (byte* or = Original)
                {
                    adjustb((byte*)bitdata.Scan0.ToPointer(), (short)trackCPP.Value, imagesize, or); 

                }


            }
            stopCPP.Stop();
            labelCPP.Text = stopCPP.ElapsedTicks.ToString();
            stopCPP.Reset();
            pic.Image = bmpFront;
            bmpFront.UnlockBits(bitdata);


        }
        [DllImport("mehlib.dll")]
        static unsafe extern void adjustASMadap(byte* source, short bar, Int32 size, byte* ori);
        
        private void trackASM_Scroll(object sender, EventArgs e)
        {
            bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            stopASM.Start();
            unsafe
            {
                fixed (byte* or = Original)
                {
                    adjustASMadap((byte*)bitdata.Scan0.ToPointer(), (short)trackASM.Value, imagesize, or);

                }


            }
            stopASM.Stop();
            labelASM.Text = stopASM.ElapsedTicks.ToString();
            stopASM.Reset();
            pic.Image = bmpFront;
            bmpFront.UnlockBits(bitdata);




        }

        public int flag;
        public bool incflag()
        {
            flag++;
            if (flag > 3)
                return true;
            else return false;
        }



        private void findCToolStripMenuItem_Click(object sender, EventArgs e)
        {
             bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

            stopCsharp.Start();
            unsafe
            {
                byte* norm = (byte*)bitdata.Scan0.ToPointer();

                //yukariyida fixlememiz gerekiyo glba
                fixed (byte* or = Original)
                {
                    for (int i = 2; i < imagesize; i+=3)
                    {
                        if (norm[i] > 150)
                        {
                            if(norm[i-2]<90&&norm[i-1]<90){
                                incflag();
                                if(incflag()){
                                    for(int j = i-30;j<i;j++){
                                        norm[j] = 0;
                                    }
                                }
                            } 
                        }
                        }
                

                    }


                }
      






                stopCsharp.Stop();
                labelCS.Text = stopCsharp.ElapsedTicks.ToString();
                stopCsharp.Reset();
                pic.Image = bmpFront;

                bmpFront.UnlockBits(bitdata);
            }

        private int flag2=0;
        private void incflag2(){
            flag2++;


        }



        private void findC2ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            string asd = null;

            for (int i = 0; i < Original.Length; i++)
            {
                asd += (string)(Original + " ");
                if ((i % 3) == 0)
                    asd += "  ";
            }
            System.IO.File.WriteAllText(@"M:\lol.txt", asd);

        }
   }


}
