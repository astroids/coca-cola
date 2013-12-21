using AForge.Video.FFMPEG;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AForge.Video;
using AForge.Video.DirectShow;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace Coca_cola
{
    public partial class Form1 : Form
    {
        private FilterInfoCollection VideoCaptureDevices;
        private VideoCaptureDevice FinalVideo;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(FinalVideo.IsRunning == true) FinalVideo.Stop();
            FinalVideo = new VideoCaptureDevice(VideoCaptureDevices[comboBox1.SelectedIndex].MonikerString);
            FinalVideo.NewFrame += FinalVideo_NewFrame;
            FinalVideo.Start();
            
        }
        [DllImport("mehlib.dll")]
        static unsafe extern void searchrw(byte* sour, Int32 imgSize, Int32 vertical);
        public static Rectangle picRect;
        public BitmapData bitdata;
        private int vert;
        private static Int32 imagesize = 0;

        void FinalVideo_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            Bitmap video = (Bitmap)eventArgs.Frame.Clone();
            imagesize = video.Width * video.Height * 3;
            vert = video.Width;
            bitdata = video.LockBits(picRect, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            unsafe
            {
                searchrw((byte*)bitdata.Scan0.ToPointer(), imagesize, vert);
            }
            picBox.Image = video;
            video.UnlockBits(bitdata);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            VideoCaptureDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            foreach (FilterInfo vid in VideoCaptureDevices)
            {
                comboBox1.Items.Add(vid.Name);
            }
            comboBox1.SelectedIndex = 0;
            FinalVideo = new VideoCaptureDevice();


        }
    }
}
