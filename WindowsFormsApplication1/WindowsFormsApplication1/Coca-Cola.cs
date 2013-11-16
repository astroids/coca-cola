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
using System.Text;

/*
TO DO LIST
 * 
 * Fonksiyonlari namespacelere ayir
 * 
 * 
 * 

 * 1)fix handles
 * 2)write in ASM
 * 3)start second algorithms if above works 
 * 
 * 
 * NON IMPORTANT STUFF
 * 1)reset trackbar after every pic load
 * 2)text format
 * 3)del unused funs
 * 







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
                        findToolStripMenuItem.Enabled = true;
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
            bitdata = source.LockBits(picRect, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
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
                fixed (byte* or = Original)
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
                    for (int i = 2; i < imagesize; i += 3)
                    {
                        if (norm[i] > 85)
                        {
                            if (norm[i - 2] < 30 && norm[i - 1] < 30)
                            {
                                incflag();
                                if (incflag())
                                {
                                    for (int j = i - 30; j < i; j++)
                                    {
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

        private int flag2 = 0;
        private void incflag2()
        {
            flag2++;


        }



        private void findC2ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            string asd = null;
            bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

            stopCsharp.Start();
            unsafe
            {
                byte* norm = (byte*)bitdata.Scan0.ToPointer();
                for (int i = 0; i < Original.Length; i++)
                {
                    asd += (string)(norm[i] + " ");
                    if ((i % 3) == 0)
                    {
                        asd += "  ";
                    }
                }
                System.IO.File.WriteAllText(@"lol.txt", asd);
            }
        }

        private int redFlag = 0;
        private int whiteFlag = 0;
        private int paras = 0;
        private void incRed()
        {
            redFlag++;
        }

        private void incWhite()
        {
            whiteFlag++;

        }

        private unsafe bool isItRed(byte* norm, int i)
        {
            if (norm[i] > 79)
            {
                if (norm[i - 2] < 41 && norm[i - 1] < 41)
                {
                    incRed();
                    return true;
                }
                else return false;
            }
            else return false;


        }
        private void resetRWFlags()
        {
            redFlag = 0;
            whiteFlag = 0;

        }




        private void rWFindCToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

            stopCsharp.Start();
            unsafe
            {
                byte* norm = (byte*)bitdata.Scan0.ToPointer();
                for (int i = 0; i < Original.Length; i++)
                {
                    if ((isItRed(norm, i) == false) && redFlag > 0)
                    {
                        if (!isItWhite(norm, i))
                        {
                            fadeToBlack(norm, i);
                            resetRWFlags();

                        }
                        else resetRWFlags();
                    }
                    else resetRWFlags();

                }
            }
            stopCsharp.Stop();
            labelCS.Text = stopCsharp.ElapsedTicks.ToString();
            stopCsharp.Reset();
            pic.Image = bmpFront;

            bmpFront.UnlockBits(bitdata);
        }

        private unsafe void fadeToBlack(byte* norm, int from)
        {
            from -= ((whiteFlag + redFlag) * 3);

            for (int i = 0; i < from; i++)
            {
                norm[from] = 0;
            }
        }

        private unsafe bool isItWhite(byte* norm, int i)
        {
            if (norm[i] > 120)
            {
                if (norm[i - 2] < 120 && norm[i - 1] < 120)
                {
                    incWhite();
                    return true;
                }
                else return false;
            }
            else return false;
        }






        private void colorAnalizerForCpp_Click(object sender, EventArgs e)
        {
            string asd = null;
            bitdata = bmpFront.LockBits(picRect, ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

            stopCsharp.Start();
            unsafe
            {
                byte* norm = (byte*)bitdata.Scan0.ToPointer();
                for (int i = 0; i < Original.Length; i++)
                {
                    asd += (string)(norm[i]+"");
                    asd += "\x0d\x0a";// new line
                    
                }
                System.IO.File.WriteAllText(@"lolCpp.txt", asd);
            }
            bmpFront.UnlockBits(bitdata);
            MessageBox.Show("Finished");
        }
      

    }
    void stateRWRW();
void incPara();
void fadeToBlack();
void resetRWFlags();
void print();


size_t firstPhase;
size_t picsize = 0;
std::vector<unsigned short> pic;
std::ifstream f("lolcpp.txt");
int red1 = 0;
int red2 = 0;
int white1 = 0;
int white2 = 0;
int paras = 0;
size_t mainL;									/* bu sayi parametre  olarak gelmesi lzmmmm !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* dll yazarken async calismazsa buraya baaakkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk*/




//////////////////////////////////   MAIN
void main(){

	readFile();
	//print();
	std::cout << pic.size() << std::endl;
	picsize = pic.size();
	system("pause");

	mainL = 2;
	STATE0();
	std::cout << "Fin" << std::endl;
	system("pause");
}

void readFile(){
	unsigned short temp;

	if (f){
		while (f.good())
		{
			f >> temp;
			pic.push_back(temp);
		}
	}

}
void print(){
	for (size_t i = 0; i < pic.size(); i++)
	{
		std::cout << pic[i] << " ";
		if ((i % 3) == 0){
			std::cout << "-- ";
		}if (i % 12 == 0){
			std::cout << std::endl;
		}
	}

}




//////////////////////////		DEBUGGER
void fadeToBlack()
{
#ifdef FADE
	size_t from = mainL - ((white1 + red1) * 3);
	//	std::cout << "fading-----------" << std::endl;
	//if ((mainL - from)>200){
	std::cout << mainL - from << std::endl;

	//system("pause");

	for (size_t i = from; i < mainL; i++)
	{
		pic[i] = 0;
		std::cout << pic[i] << " ";
		if ((i % 3) == 0)std::cout << "\n";

	}
	//	std::cout << "-----------------------------------------" << std::endl;


#endif
}
//////////////////////////		DEBUGGER


//////////////////////////////////////					STATE 0000000000000000000000000000000000
void STATE0()
{
	/// kirmizimi testi       for (mainL = 2; mainL < pic.size() ; mainL+=3) offfff 2den basla
	for (mainL; mainL < 1000; mainL += 3)
	{
		if (pic[mainL] > RTr)
		{
			if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg)
			{
				stateR();

			}

		}
	}

}












////////////////////////////////////					STATE 1111111111111111111111111111111111111  burada firstphase gereksiz olabilir
bool stateR() {
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3)
	{
		//ilk 10 pixel kirmizi değilse direk don				
		if (pic[mainL] < RTr)
		{
			return false;

		}if ((pic[mainL - 2]) > RTb && (pic[mainL - 1]) > RTg)
		{
			return false;
		}
	}
	red1 = 11;


	/// artik kirmizimi deilse beyazmı
	for (mainL; mainL < LIMI; mainL += 3)
	{
		if (pic[mainL] > RTr) {
			if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg){
				red1++;
			}
			else if (pic[mainL] > Wrbg){
				if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg){
					stateRW();
				}
			}
			else {
				paras++;							////////////      kirmizi paraziti bu değeri ince ayarla
				if (paras * 3 > red1){
					return false;
				}

			}

		}



	}



}


//////////////////////////////////  buradan sadece state 0 a donus var 
void stateRW(){
	paras = 0;						////////// burada geleck parazit degeri hesaplanabilir ama algoritmayi cok yavaslatabilir
	white1 = 1;

	//ilk 10 pixel
	firstPhase = mainL + 30;
	for (mainL; mainL < firstPhase; mainL += 3) {
		if ((pic[mainL] < Wrbg)){
			STATE0();
		}
		if ((pic[mainL - 2]) < Wrbg && (pic[mainL - 1] < Wrbg)) {
			STATE0();
		}
	}
	white1 += 10;

	for (mainL; mainL < LIMI; mainL += 3){
		if (pic[mainL - 2] < RTb && pic[mainL - 1] < RTg){
			if (pic[mainL]>RTr){
				stateRWR();
			}
		}

		if (pic[mainL] > Wrbg){
			if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg) {
				white1++;
			}
		}
		else
		{
			paras++;
			if (paras * 3 > white1){
				STATE0();
			}
		}


	}
}


////////////////////////////////////////////					hic paraziti umursamiyor????????????
void stateRWR(){
	paras = 1;
	red2 = 0;
	firstPhase = mainL + (white1 * 3);
	for (mainL; mainL < firstPhase; mainL += 3)									///bu *3 ten eksik olabilir
	{
			
		if (pic[mainL] < RTr)
		{
			STATE0();

		}if ((pic[mainL - 2]) > RTb && (pic[mainL - 1] > RTg))
		{
			STATE0();
		}
	}
	red2 = red1 + 1;																		//yukariyi degistirirsen burayida degistir

	std::cout << "RWR ye kadar dogru galiba" << std::endl;
	//system("pause");
	mainL += ((red2 / 4) * 3);							//burayi napcaz bilmiyom
	stateRWRW();






}


void stateRWRW(){
	firstPhase = mainL + (white1 * 3);
	paras = (white1 / 3) + 1;
	for (mainL; mainL < white1; mainL+=3)
	{
		if (pic[mainL] > Wrbg){
			if (pic[mainL - 2] > Wrbg && pic[mainL - 1] > Wrbg) {
				white2++;
			}
			else
			{
				paras--;
				if (paras == 0){
					STATE0();
				}
			}
		}
	}
	system("pause");
	std::cout << "STATE RWRW YUPP" << std::endl;


}
}
