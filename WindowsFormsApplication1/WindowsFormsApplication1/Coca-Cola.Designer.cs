namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pic = new System.Windows.Forms.PictureBox();
            this.trackCS = new System.Windows.Forms.TrackBar();
            this.labelCS = new System.Windows.Forms.Label();
            this.menu = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openPict = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.findToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.findCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.findC2ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rWFindCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.colorAnalizerForCpp = new System.Windows.Forms.ToolStripMenuItem();
            this.findCocaColaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cocaColaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fileBrowse = new System.Windows.Forms.OpenFileDialog();
            this.trackCPP = new System.Windows.Forms.TrackBar();
            this.trackASM = new System.Windows.Forms.TrackBar();
            this.labelCPP = new System.Windows.Forms.Label();
            this.labelASM = new System.Windows.Forms.Label();
            this.videoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.pic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackCS)).BeginInit();
            this.menu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackCPP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackASM)).BeginInit();
            this.SuspendLayout();
            // 
            // pic
            // 
            this.pic.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pic.Location = new System.Drawing.Point(12, 27);
            this.pic.Name = "pic";
            this.pic.Size = new System.Drawing.Size(833, 409);
            this.pic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic.TabIndex = 1;
            this.pic.TabStop = false;
            this.pic.Click += new System.EventHandler(this.pic_Click);
            // 
            // trackCS
            // 
            this.trackCS.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackCS.Enabled = false;
            this.trackCS.Location = new System.Drawing.Point(12, 442);
            this.trackCS.Maximum = 255;
            this.trackCS.Minimum = -255;
            this.trackCS.Name = "trackCS";
            this.trackCS.Size = new System.Drawing.Size(761, 45);
            this.trackCS.TabIndex = 2;
            this.trackCS.TickFrequency = 16;
            this.trackCS.Scroll += new System.EventHandler(this.trackCS_Scroll);
            // 
            // labelCS
            // 
            this.labelCS.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.labelCS.AutoSize = true;
            this.labelCS.Location = new System.Drawing.Point(782, 452);
            this.labelCS.Name = "labelCS";
            this.labelCS.Size = new System.Drawing.Size(63, 13);
            this.labelCS.TabIndex = 3;
            this.labelCS.Text = "C# average";
            this.labelCS.Click += new System.EventHandler(this.labelCS_Click);
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.findToolStripMenuItem,
            this.openToolStripMenuItem,
            this.cocaColaToolStripMenuItem,
            this.videoToolStripMenuItem});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(868, 24);
            this.menu.TabIndex = 4;
            this.menu.Text = "menuStrip1";
            this.menu.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openPict,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // openPict
            // 
            this.openPict.Name = "openPict";
            this.openPict.Size = new System.Drawing.Size(103, 22);
            this.openPict.Text = "Op&en";
            this.openPict.Click += new System.EventHandler(this.openToolStripMenuItem_Click_1);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // findToolStripMenuItem
            // 
            this.findToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.findCToolStripMenuItem,
            this.findC2ToolStripMenuItem,
            this.rWFindCToolStripMenuItem,
            this.colorAnalizerForCpp,
            this.findCocaColaToolStripMenuItem});
            this.findToolStripMenuItem.Enabled = false;
            this.findToolStripMenuItem.Name = "findToolStripMenuItem";
            this.findToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.findToolStripMenuItem.Text = "Tools";
            // 
            // findCToolStripMenuItem
            // 
            this.findCToolStripMenuItem.Name = "findCToolStripMenuItem";
            this.findCToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.findCToolStripMenuItem.Text = "Find C#";
            this.findCToolStripMenuItem.Click += new System.EventHandler(this.findCToolStripMenuItem_Click);
            // 
            // findC2ToolStripMenuItem
            // 
            this.findC2ToolStripMenuItem.Name = "findC2ToolStripMenuItem";
            this.findC2ToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.findC2ToolStripMenuItem.Text = "C# MColor Analizer ";
            this.findC2ToolStripMenuItem.Click += new System.EventHandler(this.findC2ToolStripMenuItem_Click_1);
            // 
            // rWFindCToolStripMenuItem
            // 
            this.rWFindCToolStripMenuItem.Name = "rWFindCToolStripMenuItem";
            this.rWFindCToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.rWFindCToolStripMenuItem.Text = "RW Find C# ";
            this.rWFindCToolStripMenuItem.Click += new System.EventHandler(this.rWFindCToolStripMenuItem_Click);
            // 
            // colorAnalizerForCpp
            // 
            this.colorAnalizerForCpp.Name = "colorAnalizerForCpp";
            this.colorAnalizerForCpp.Size = new System.Drawing.Size(220, 22);
            this.colorAnalizerForCpp.Text = "C# MColor Analizer for CPP";
            this.colorAnalizerForCpp.Click += new System.EventHandler(this.colorAnalizerForCpp_Click);
            // 
            // findCocaColaToolStripMenuItem
            // 
            this.findCocaColaToolStripMenuItem.Name = "findCocaColaToolStripMenuItem";
            this.findCocaColaToolStripMenuItem.Size = new System.Drawing.Size(220, 22);
            this.findCocaColaToolStripMenuItem.Text = "Find Coca-Cola";
            this.findCocaColaToolStripMenuItem.Click += new System.EventHandler(this.findCocaColaToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(48, 20);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click_2);
            // 
            // cocaColaToolStripMenuItem
            // 
            this.cocaColaToolStripMenuItem.Name = "cocaColaToolStripMenuItem";
            this.cocaColaToolStripMenuItem.Size = new System.Drawing.Size(75, 20);
            this.cocaColaToolStripMenuItem.Text = "Coca-Cola";
            this.cocaColaToolStripMenuItem.Click += new System.EventHandler(this.cocaColaToolStripMenuItem_Click);
            // 
            // fileBrowse
            // 
            this.fileBrowse.FileName = "openFileDialog1";
            this.fileBrowse.Filter = "Pictures|*.jpg;*.bmp;*.jpeg;";
            this.fileBrowse.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // trackCPP
            // 
            this.trackCPP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackCPP.Enabled = false;
            this.trackCPP.Location = new System.Drawing.Point(12, 493);
            this.trackCPP.Maximum = 255;
            this.trackCPP.Minimum = -255;
            this.trackCPP.Name = "trackCPP";
            this.trackCPP.Size = new System.Drawing.Size(761, 45);
            this.trackCPP.TabIndex = 5;
            this.trackCPP.TickFrequency = 16;
            this.trackCPP.Scroll += new System.EventHandler(this.trackCPP_Scroll);
            // 
            // trackASM
            // 
            this.trackASM.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.trackASM.Enabled = false;
            this.trackASM.Location = new System.Drawing.Point(12, 532);
            this.trackASM.Maximum = 255;
            this.trackASM.Minimum = -255;
            this.trackASM.Name = "trackASM";
            this.trackASM.Size = new System.Drawing.Size(761, 45);
            this.trackASM.TabIndex = 6;
            this.trackASM.TickFrequency = 16;
            this.trackASM.Scroll += new System.EventHandler(this.trackASM_Scroll);
            // 
            // labelCPP
            // 
            this.labelCPP.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.labelCPP.AutoSize = true;
            this.labelCPP.Location = new System.Drawing.Point(782, 493);
            this.labelCPP.Name = "labelCPP";
            this.labelCPP.Size = new System.Drawing.Size(68, 13);
            this.labelCPP.TabIndex = 7;
            this.labelCPP.Text = "C++ average";
            // 
            // labelASM
            // 
            this.labelASM.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.labelASM.AutoSize = true;
            this.labelASM.Location = new System.Drawing.Point(782, 532);
            this.labelASM.Name = "labelASM";
            this.labelASM.Size = new System.Drawing.Size(72, 13);
            this.labelASM.TabIndex = 8;
            this.labelASM.Text = "ASM average";
            // 
            // videoToolStripMenuItem
            // 
            this.videoToolStripMenuItem.Name = "videoToolStripMenuItem";
            this.videoToolStripMenuItem.Size = new System.Drawing.Size(49, 20);
            this.videoToolStripMenuItem.Text = "Video";
            this.videoToolStripMenuItem.Click += new System.EventHandler(this.videoToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(868, 589);
            this.Controls.Add(this.labelASM);
            this.Controls.Add(this.labelCPP);
            this.Controls.Add(this.trackASM);
            this.Controls.Add(this.trackCPP);
            this.Controls.Add(this.labelCS);
            this.Controls.Add(this.trackCS);
            this.Controls.Add(this.pic);
            this.Controls.Add(this.menu);
            this.Name = "Form1";
            this.Text = "Coca-Cola";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackCS)).EndInit();
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackCPP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackASM)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pic;
        private System.Windows.Forms.TrackBar trackCS;
        private System.Windows.Forms.Label labelCS;
        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.OpenFileDialog fileBrowse;
        private System.Windows.Forms.TrackBar trackCPP;
        private System.Windows.Forms.TrackBar trackASM;
        private System.Windows.Forms.Label labelCPP;
        private System.Windows.Forms.Label labelASM;
        private System.Windows.Forms.ToolStripMenuItem findToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem findCToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem findC2ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem rWFindCToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem colorAnalizerForCpp;
        private System.Windows.Forms.ToolStripMenuItem findCocaColaToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cocaColaToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openPict;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem videoToolStripMenuItem;
    }
}

