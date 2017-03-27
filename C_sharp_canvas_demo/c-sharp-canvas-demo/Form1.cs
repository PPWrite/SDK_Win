using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;


namespace c_sharp_demo
{
    public partial class Form1 : Form
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Test
        {
            public int nPens;  // 笔状态
            public int nX;     // 笔x轴坐标
            public int nY;     // 笔y轴坐标
            public int nPenP;  // 笔压力
        }

        // 获取dll导出函数
        //[DllImport("usbDevModule.dll", CharSet = CharSet.Ansi/*, CallingConvention = CallingConvention.StdCall*/)]
        //public static extern IntPtr createObj();

        public delegate void DataCallBack(string pUsbData, ref Test test);

        [DllImport("usbDevModule.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool _extern_openSpecUsbDevByPid(string[] str, int nSize, DataCallBack ps);

        [DllImport("usbDevModule.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool _extern_CloseUsbDev();

        [DllImport("User32")]
        public extern static void SetCursorPos(int x, int y);

        /*[UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.ThisCall)]
        private delegate bool fun_handler([In] IntPtr @this, [In] char[][] p, [In] int nSize, [In] IntPtr ptr);
        private delegate bool fun_handler2([In] IntPtr @this);
        private delegate int fun_handler_test([In] IntPtr p, string str);
        //         private static T GetInterfaceMethod<T>(IntPtr ptrInterFace, int method)
        //         {
        //             return (T)(Object)Marshal.GetDelegateForFunctionPointer(am)
        //         }

        private static T GetInterfaceMethod<T>(IntPtr ptrInterface, int method)
        {
            return (T)(Object)Marshal.GetDelegateForFunctionPointer(Marshal.ReadIntPtr(Marshal.ReadIntPtr(ptrInterface, 0 * Marshal.SizeOf(typeof(IntPtr))), method * Marshal.SizeOf(typeof(IntPtr))), typeof(T));
        }

        public static void openUsb(IntPtr ptrC)
        {
            //             fun_handler fun_callback = (fun_handler)Marshal.GetDelegateForFunctionPointer(Marshal.ReadIntPtr(Marshal.ReadIntPtr(ptrC, 0*Marshal.SizeOf(typeof(IntPtr))), 0*Marshal.SizeOf(typeof(IntPtr))),
            //                 typeof(fun_handler));
            //             string[] stringArry = new string[2];
            //             stringArry[1] = ("7806");
            //             string ss = "7806";
            //             //char[] cc = ss.ToCharArray();
            //             char pTemp[2][30]  = {"7806", "7807"};
            //             //pTemp[0] = "7806";
            //             IntPtr ptrTemp = IntPtr.Zero;
            //             bool result = fun_callback(ptrC, pTemp, 1, ptrTemp);
        }

        public static void closeUsb(IntPtr ptrC)
        {
            return;
            fun_handler2 fun_callback = GetInterfaceMethod<fun_handler2>(ptrC, 2);//(fun_handler2)Marshal.GetDelegateForFunctionPointer(Marshal.ReadIntPtr(Marshal.ReadIntPtr(ptrC, 0 * Marshal.SizeOf(typeof(IntPtr))), 2 * Marshal.SizeOf(typeof(IntPtr))),typeof(fun_handler2));
            bool result = fun_callback(ptrC);
        }

        public static void test(IntPtr ptrC)
        {
            fun_handler_test test_fun = GetInterfaceMethod<fun_handler_test>(ptrC, 0);
            string strFileName = @"D:\testFile.txt";
            IntPtr init = Marshal.StringToHGlobalAnsi(strFileName);
            //string modality = System.Runtime.InteropServices.Marshal.PtrToStringAnsi();
            byte[] byteArray = System.Text.Encoding.ASCII.GetBytes(strFileName);
            int bRes = test_fun(ptrC, strFileName);
            bRes = bRes;
        }*/

        private static string m_strData;

        private static Queue<Test> qData = new Queue<Test>();
        private static System.Object lockThis = new System.Object();
        private static void test_data(string pUsbData, ref Test test)
        {
            //this.setText(pUsbData);
            //m_strData += pUsbData;
            Console.WriteLine("{0}", test.nPens);
            lock (lockThis)
            {
                qData.Enqueue(test);
            }
            
            mEvent.Set();
            return;
        }

        private DataCallBack m_ps;
        public bool openUsbDev()
        {
            string[] str = new string[2];
            str[0] = "7806";
            str[1] = "781e";
            m_ps = new DataCallBack(test_data);
            bool bRs = _extern_openSpecUsbDevByPid(str, 2, m_ps);
            return bRs;
        }

        public bool closeUsbDev()
        {
            return _extern_CloseUsbDev();
        }

        public Form1()
        {
            InitializeComponent();

            pictureBox1.MouseDown += new MouseEventHandler(Pic_OnMouseClick);
            pictureBox1.MouseMove += new MouseEventHandler(Pic_OnMouseMove);
            pictureBox1.MouseUp += new MouseEventHandler(Pic_OnMouseUp);
            pictureBox1.Resize += new EventHandler(Pic_Resize);
            pictureBox1.Paint += new PaintEventHandler(Pic_OnPaint);
        }

        delegate void SetTextCallBack(string strText);

        private void setText(string text)
        {
            //try
            {
                if (this.textBox1.InvokeRequired)
                {
                    while (!this.textBox1.IsHandleCreated)
                    {
                        if (this.textBox1.Disposing || this.textBox1.IsDisposed)
                        {
                            return;
                        }
                    }
                    SetTextCallBack d = new SetTextCallBack(setText);
                    this.textBox1.Invoke(d, new object[] { text });
                }
                else
                {
                    this.textBox1.Text = text;
                }
            }
            //catch (System.Exception ex)
            //{
            //	string str = ex.Message;
            //}
        }

        /*private Thread thread;
        private void test_thread_fun()
        {
            while (true)
            {
                this.setText("你好");
                System.Threading.Thread.Sleep(1000);
            }
            this.openUsbDev();
        }*/
        private bool mThreadCreateFlag = true;
        private void button1_Click(object sender, EventArgs e)
        {
            //             this.thread = new Thread(new ThreadStart(this.test_thread_fun));
            //             return;
            this.button1.Text = "正在打开设备....";
            this.button1.Enabled = false;

            if (mThreadCreateFlag)
            {
                this.thread = new Thread(new ThreadStart(this.updateTextValue));
                this.thread.Start();
                mThreadCreateFlag = false;
            }
            
            if (!openUsbDev())
            {
                this.button1.Enabled = true;
                this.button1.Text = "设备打开失败(重试)";
            }
            else
            {
                this.button1.Text = "设备打开成功....";
                this.button2.Enabled = true;
            }
        }

        private static AutoResetEvent mEvent = new AutoResetEvent(false);
        private bool m_bRuning = true;
        private Thread thread;

        private static int nFlags = 0;
        private PointF m_point;
        private int m_nPenStatus = 0;
        private void updateTextValue()
        {
            while (m_bRuning)
            {
                
                mEvent.WaitOne();
                if (m_bRuning)
                {
                    // 优先调用界面显示
                    //if ()
                    Queue<Test> qTmpData = new Queue<Test>();
                    lock (lockThis)
                    {
                        while (qData.Count > 0)
                        {
                            qTmpData.Enqueue(qData.Dequeue());
                        }
                    }
//                     Test data;
//                     lock (lockThis)
//                     {
//                         data = qData.Dequeue();
//                     }
// 
//                     lock (lockThis)
//                     {
//                         qData.Enqueue(test);
//                     }
                    while(qTmpData.Count > 0)
                    {
                        Test data = qTmpData.Dequeue();
                        PointF pointf = new PointF(data.nX, data.nY);
                        if (pointIsInvalid(data.nPens, ref pointf))
                        {
                            if (data.nPens == 17 && nFlags == 0)  // 笔接触到板子
                            {
                                nFlags = 1;
                                compressPoint(ref pointf);
                                onbegin(ref pointf);
                                moveCursor( pointf);
                                m_bDrawingType = true;

                            //Console.WriteLine("pen in pens = {0}", data.nPens);
                            }
                            else if (data.nPens == 17 && nFlags == 1)
                            {
                                compressPoint(ref pointf);
                                onDrawing(ref pointf, data.nPenP);
                                moveCursor( pointf);
                            //Console.WriteLine("wirting");
                            }
                            else if ((data.nPens == 16 || data.nPens == 0) && nFlags == 1)   // 笔离开板子
                            {
                                if (nFlags == 1)
                                    endTrack(true);
                                else
                                    endTrack(false);
                                nFlags = 0;
                                m_bDrawingType = false;
                            //Console.WriteLine("pen leave pens = {0}", data.nPens);
                            }

                            if (data.nPens == 16)
                            {
                                compressPoint(ref pointf);
                                moveCursor( pointf);
                            //Console.WriteLine("moveing");
                            }
                        }
                    }

                    //this.setText(m_strData);
                }
            }
        }

        // 
        private double nCompress = (double)(17407 / 1000);
        private void compressPoint(ref PointF point)
        {
            float nx = (float)(point.X / nCompress);
            float ny = (float)(point.Y / nCompress);
            point.X = nx;
            point.Y = ny;
        }

        private bool pointIsInvalid( int nPenStatus,  ref PointF pointValue )
        {
            if ((m_point == pointValue) && (m_nPenStatus == nPenStatus))
                return false;
            m_point = pointValue;
            m_nPenStatus = nPenStatus;
            return true;
        }

        delegate void MoveCurrorCallBack(PointF point);
        private void moveCursor( PointF pos)
        {


            if (this.pictureBox1.InvokeRequired)
                {
                    while (!this.pictureBox1.IsHandleCreated)
                    {
                        if (this.pictureBox1.Disposing || this.pictureBox1.IsDisposed)
                        {
                            return;
                        }
                    }
                    MoveCurrorCallBack d = new MoveCurrorCallBack(moveCursor);
                    this.pictureBox1.Invoke(d, new object[] {  pos });
                }
                else
                {
                    Point p = new Point();
                    p.X = (int)pos.X;
                    p.Y = (int)pos.Y;
                    p = pictureBox1.PointToScreen(p);
                    SetCursorPos(p.X, p.Y);
                }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            closeUsbDev();
            this.button2.Enabled = false;
            this.button1.Enabled = true;
            this.button1.Text = "打开设备";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            m_strData = "";
            this.textBox1.Text = m_strData;
        }

        public void clearResource()
        {
            if (mThreadCreateFlag == false)
            {
                m_bRuning = false;
                mEvent.Set();
                this.thread.Join();
                closeUsbDev();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            this.textBox1.SelectionStart = this.textBox1.Text.Length; //Set the current caret position at the end
            this.textBox1.ScrollToCaret(); //Now scroll it automatically
        }


        private List<CavsItem> m_item = new List<CavsItem>();
        private List<PointF> m_lastPoints = new List<PointF>();
        private bool m_bDrawing = false;
        private bool m_bDrawingType = true;
        private PointF m_lastPoint;
        private CavsItem m_currentItem;

        protected override void OnPaint(PaintEventArgs e)
        {
            //updateLine();
            //Graphics grap =  CreateGraphics();
            //grap.DrawLine(new Pen(Color.Red, 2), 20, 20, 40, 40);
        }

        private void onbegin(ref PointF pos, int nCompress = 0)
        {
            m_bDrawing = true;
            Console.WriteLine("m_bDrawing == true");
            m_lastPoint = pos;
            CavsItem item = new CavsItem(); // = new CavsItem；
            item.listpoints = new List<PointF>();
            item.beginPoint = pos;
            m_currentItem = item;
        }
        public object obj = new object();
        private void onDrawing(ref PointF pos, int nCompress = 0)
        {
            if (!m_bDrawing || !m_bDrawingType)
                return;
            doDrawing(ref pos, nCompress);
            lock(obj)
            {
                m_currentItem.listpoints.Add(pos);
            }
         }


        private void doDrawing(ref PointF pos, int nCompress = 0)
        {
            Graphics grap = pictureBox1.CreateGraphics();
            //grap.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceOver;
            
           // grap.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighQuality;
            grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
            //grap.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;

            //grap.SetCompositingQuality(CompositingQualityHighSpeed);
            //float fCompress = getCompress(nCompress, 2);
           // Console.WriteLine("fCompress={0} nCompress={1}", fCompress, nCompress);

            grap.DrawLine(new Pen(Color.Black, 2), m_lastPoint, pos);
	        m_lastPoint = pos;
            grap.Dispose();

            if (pos.X == 0)
            {
                int n = 0;
            }
            //Update();
        }

        private void endTrack(bool bSave = true)
        {

            onEnd();
            //QVector<QSharedPointer<CanvasItem>> items;
            //items.push_back(m_currentItem);
            //addItems(items);
            //m_currentItem.clear();
            if (m_currentItem.listpoints == null || bSave == false)
            {
                return;
            }
            m_item.Add(m_currentItem);
        }

        private void onEnd()
        {
            m_bDrawing = false;
            Console.WriteLine("m_bDrawing == false");
            
        }
        // protected override void OnMouse
        protected void Pic_OnMouseClick(object sender, MouseEventArgs e)
        {
            m_bDrawingType = true;
            PointF f = new PointF(e.Location.X, e.Location.Y);
            onbegin(ref f);
            //base.OnMouseClick(e);
        }

        protected void Pic_OnMouseMove(object sender, MouseEventArgs e)
        {
            PointF f = new PointF(e.Location.X, e.Location.Y);
            onDrawing(ref f);
            //base.OnMouseMove(e);
        }

        protected void Pic_OnMouseUp(object sender, MouseEventArgs e)
        {
            m_bDrawingType = false;
            endTrack();
            //base.OnMouseUp(e);
        }

        protected void Pic_Resize(object sender, EventArgs e)
        {
            updateLine();
        }

        protected void Pic_OnPaint(object sender, PaintEventArgs e)
        {
            //updateLine();
            pictureBox1.BackColor = Color.White;

            foreach (CavsItem item in m_item)
            {
                if (item.listpoints == null)
                {
                    continue;
                }
                Graphics grap = pictureBox1.CreateGraphics();
                e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                e.Graphics.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                int nSize = item.listpoints.Count + 1;
                PointF[] pointsize = new PointF[nSize];
                //PointF tmpPoint = item.beginPoint;
                //onbegin(ref tmpPoint);
                pointsize[0] = item.beginPoint;

                PointF pointTemp = item.beginPoint;
                for (int i = 0; i < item.listpoints.Count; ++i)
                {
                    //tmpPoint = item.listpoints[i];
                    //onDrawing(ref tmpPoint);
                    //grap.DrawLine(new Pen(Color.Black, 2), pointTemp, item.listpoints[i]);
                    //pointTemp = item.listpoints[i];
                    pointsize[i + 1] = item.listpoints[i];
                }
                e.Graphics.DrawLines(new Pen(Color.Black, 2), pointsize);
               // e.Graphics.Dispose();
                //onEnd();
            }

                base.OnPaint(e);
        }


        private void updateLine()
        {
            pictureBox1.Visible = true;



            foreach (CavsItem item in m_item)
            {
                Graphics grap = pictureBox1.CreateGraphics();
                grap.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                grap.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                grap.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                int nSize = item.listpoints.Count + 1;
                PointF[] pointsize = new PointF[nSize];
                //PointF tmpPoint = item.beginPoint;
                //onbegin(ref tmpPoint);
                pointsize[0] = item.beginPoint;

                PointF pointTemp = item.beginPoint;
                for (int i = 0; i < item.listpoints.Count; ++i )
                {
                    //tmpPoint = item.listpoints[i];
                    //onDrawing(ref tmpPoint);
                    //grap.DrawLine(new Pen(Color.Black, 2), pointTemp, item.listpoints[i]);
                    //pointTemp = item.listpoints[i];
                    pointsize[i+1] = item.listpoints[i];
                }
                grap.DrawLines(new Pen(Color.Black, 2), pointsize);
                grap.Dispose();
                //onEnd();
            }
            
        }


        // 画布清空
        private void button4_Click(object sender, EventArgs e)
        {
            m_item.Clear();
            if (this.Visible == false)
            {
                this.Visible = true;
            }
            else
                this.Visible = false;
            this.Show();
        }

        // 获取压感值
        private float getCompress(int nPenC, int nWidth)
        {
            return (float)(((float)nPenC / 950) * nWidth);
        }
    }

    public struct CavsItem
    {
        public PointF beginPoint {get; set;}
        public List<PointF> listpoints;
    }
}
