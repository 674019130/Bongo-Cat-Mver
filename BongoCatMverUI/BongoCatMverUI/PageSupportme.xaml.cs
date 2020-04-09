﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MyWpfApp
{
    /// <summary>
    /// PageSupportme.xaml 的交互逻辑
    /// </summary>
    public partial class PageSupportme : Page
    {
        public PageSupportme()
        {
            InitializeComponent();
        }



        private void click_bilibili(object sender, MouseButtonEventArgs e)
        {
            Process proc = new System.Diagnostics.Process();
            proc.StartInfo.FileName = "https://space.bilibili.com/5808772";
            proc.Start();
        }

        private void click_aifadian(object sender, MouseButtonEventArgs e)
        {
            Process proc = new System.Diagnostics.Process();
            proc.StartInfo.FileName = "https://afdian.net/@MMmmmoko";
            proc.Start();
        }
    }
}
