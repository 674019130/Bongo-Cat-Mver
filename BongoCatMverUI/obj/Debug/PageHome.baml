   M S B A M L   `   `   `  ����I  EBongoCatMverUI, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null#clr-namespace:MyWpfAppMyWpfApp  5          MyWpfApp.PageHome   5      \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      U QMaterialDesignThemes.Wpf, Version=3.0.1.920, Culture=neutral, PublicKeyToken=nullFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5      "localclr-namespace:MyWpfApp  5      -   5          N� Title$  Page1��5
       N� 
Background
 ���� $
��1000��6D   $	��Top=�6Q    � 	Resources 5       �� MergedDictionaries �� Source�� 5   
    5      �� 5      $z tpack://application:,,,/MaterialDesignColors;component/Themes/Recommended/Primary/MaterialDesignColor.DeepPurple.xaml?�6%   �� 5      $s mpack://application:,,,/MaterialDesignColors;component/Themes/Recommended/Accent/MaterialDesignColor.Lime.xaml?�6%   �� 5      $h bpack://application:,,,/MaterialDesignThemes.Wpf;component/Themes/MaterialDesignTheme.Defaults.xaml?�6%   �� 5      $f `pack://application:,,,/MaterialDesignThemes.Wpf;component/Themes/MaterialDesignTheme.Button.xaml?�6%   �� 5      $h bpack://application:,,,/MaterialDesignThemes.Wpf;component/Themes/MaterialDesignTheme.PopupBox.xaml?�6%   �� 5      $i cpack://application:,,,/MaterialDesignThemes.Wpf;component/Themes/MaterialDesignTheme.TextBlock.xaml?�6%   �� 5      $o ipack://application:,,,/MaterialDesignColors;component/Themes/MaterialDesignColor.Green.Named.Primary.xaml?�6%   �� 5      $ Bongocat_BtnStyle.xaml?�6%   %    5      .��5-      � $
��1000��6   $	��620��6   $
��Left=�6%   
������  � RowDefinitions 5.   
   �� 5/      $
��123* �6   �� 50      $	��32* �6   .+�53   
   �� $��0,20,845,192q�6   ���	#01FFFFFF6*   #  MaterialDesignThemes.Wpf.Card  54   
   $
��Left=�6   $	��600��69   $��
155,20,0,0q�6F   $	��Top=�6Z   $	��800��6r   $��2��6   .��55       � -   5        $��	Show_Page��55   E   $��Frame��6     � NavigationUIVisibility$ Hidden=�6%     � Source$ setting_cat.xaml?�6V   56      � 57   
   $	��200��6   $	��200��6   $��0,20,0,0q�6*   $
��Left=�6<   $��2��6W   .+�58      � $��0,6,0,4q�6   .+�5D      �� -   5         ��Name$ button_tutorial��5D      ���	#FFFFA0E1���	#DDFFFFFF$��0,50,50,490q�6w   $
��Auto��6�      BongoCat_ManuButton#��[  6�   ��6I   Z� .��5E      �� 	 �� Orientation$	 
Horizontal=�6!   .+�5F      '  !MaterialDesignThemes.Wpf.PackIcon  
   Kind$
 BookOpenVariant=�5G      $��28.667��5H      $��25.833��5I      $��0,0,10,0q�6,   �� 5J      -   5         ��Name$ text_tutorial��5J   $   $
��Wrap=�6;   $��使用教程��6O   $��Center=�6[   $��Center=�6x   $��Normal"�6�   $��20(�6�   $��27��6�   5K      5L      �� 5V      -   5        $% button_feedback_and_communicate��5V      ���	#FFFFA0E1���	#DDFFFFFF$��0,100,50,440q�6�   $
��Auto��6�   #��[  6�   ��6Y   Z� .��5W      �� $	 
Horizontal=�6!   .+�5X        $
 MessageProcessingOutline=�5Y      $��28.667��5Z      $��25.833��5[      $��0,0,10,0q�6,   �� 5\      $
��Wrap=�6$   $��反馈交流��68   $��Center=�6D   $��Center=�6a   $��Normal"�6}   $��20(�6�   $��27��6�   5]      5^      �� 5_      -   5        $ button_download_updates��5_      ���	#FFFFA0E1���	#DDFFFFFF$��0,150,50,390q�6   $
��Auto��6�   #��[  6�   ��6Q   Z� .��5`      �� $	 
Horizontal=�6!   .+�5a        $
 ArrowCollapseDown=�5b      $��28.667��5c      $��25.833��5d      $��0,0,10,0q�6,   �� 5e      $
��Wrap=�6$   $��下载更新��68   $��Center=�6D   $��Center=�6a   $��Normal"�6}   $��20(�6�   $��27��6�   5f      5g      �� 5h      -   5        $ button_donate��5h      ���	#FFFFA0E1���	#DDFFFFFF$��0,200,50,340q�6u   $
��Auto��6�   #��[  6�   ��6G   Z� .��5i      �� $	 
Horizontal=�6!   .+�5j        $
 FlashOutline=�5k      $��28.667��5l      $��25.833��5m      $��0,0,10,0q�6,   �� 5n      $
��Wrap=�6$   $��支持作者��68   $��Center=�6D   $��Normal"�6`   $��20(�6t   $��Center=�6�   $��80��6�   $��27��6�   5o      5p      �� 5|      -   5        $ botton_cat_set��5|      ���	#FFFFA0E1���	#DDFFFFFF$��
0,0,50,540q�6v   $
��Auto��6�   #��[  6�   ��6H   Z� .��5      �� $	 
Horizontal=�6!   $��Center=�6:   $��Center=�6U   .+�5�      � $��28.667��6   $��25.833��6/   $��0,0,10,0q�6>   .+�5�      �� $��A��6(   $��20(�61   $��./Resources/#caticon)�6?   $��Center=�6b   $��Bottom=�6   $��Normal"�6�   $��2,0,1.833,2.667q�6�   5�      �� 5�      $
��Wrap=�6$   $��猫咪设置��68   $��Center=�6D   $��Center=�6a   $��Normal"�6}   $��20(�6�   $��27��6�   5�      5�      5�      5�      �� 5�   
   $
��Left=�6   $��60��6/   $��	934,6,0,0q�6;   $	��Top=�6N   $��60��6f   ���	#00933636 � Triggers 5�      :� 5�       :� RoutedEvent$ 
MouseEnter��6   [�5�      �� 5�      .��5�      �� .��5�   "   W� 	 W� To$ 1X�62    �� 
TargetName$ close_btn_scale��69    �� TargetProperty$ ScaleX�6a    g� Duration$ 0:0:0.1D�6�   W� 5�   "   $ 1X�62   $ close_btn_scale��6;   $ ScaleY�6c   $ 0:0:0.1D�6�   5�      5�      5�      :� 5�      $ 
MouseLeave��6   [�5�      �� 5�      .��5�      �� .��5�   "   W� $	 0.7X�62   $ close_btn_scale��6;   $ ScaleX�6c   $ 0:0:0.1D�6�   W� 5�   "   $	 0.7X�62   $ close_btn_scale��6;   $ ScaleY�6c   $ 0:0:0.1D�6�   5�      5�      5�      5�      �� 5�   
   -	   5        $ btn_window_close��5�       * &MaterialDesignFloatingActionMiniButton#��[ 5�       � ToolTip$ 保存设置后关闭��5�      $��964,6,0,456q�6   $
��Auto��6B   $��30��6P    J� RenderTransformOrigin$ 0.5,0.5&�6[   $
��Left=�6�   ��6+   Z� ��5�      �� 5�      -
   5        color_close_btn�� �� Color$ 	#FFCDCDCD��5�   ;   z�5�      V� 5�      .~�5�      ��  �� ScaleX$	 0.7Q�6%    �� ScaleY$	 0.7Q�62   -   5        close_btn_scale��5�   ?   �� 5�      �� 5�      T� 5�      5�      .��5�        $
 WindowClose=�5�      $��24��5�      $��24��5�       5�      :� 5�      $ 
MouseEnter��6   [�5�      �� 5�      .��5�      �� .��5�   "   �� 	 �� To$ 	#FFFF0000X�61   $ color_close_btn��6@   $ Color�6h   $ 0:0:0.1D�6�   W� 5�   "   $ 1X�62   $ close_btn_scale��69   $ ScaleX�6a   $ 0:0:0.1D�6�   W� 5�   "   $ 1X�62   $ close_btn_scale��6;   $ ScaleY�6c   $ 0:0:0.1D�6�   5�      5�      5�      :� 5�      $ 
MouseLeave��6   [�5�      �� 5�      .��5�      �� .��5�   "   �� $ 	#FFCDCDCDX�61   $ 0:0:0.1D�6@   $ color_close_btn��6S   $ Color�6{   5�      5�      5�      5�      �� 5�   
   -   5         ��Name$ rect_move_window��5�      $
��Left=�6/   $��20��6J   $	��Top=�6V   $	��956��6n   ��5�      �� 5�      -   5        windowmove_btn_color��$ 	#526F6FC1��5�   @    5�      :� 5�      $ 
MouseEnter��6   [�5�      �� 5�      .��5�      �� .��5�   "   �� $ 	#826F6FC1X�61   $ 0:0:0.1D�6@   $ windowmove_btn_color��6S   $ Color�6�   5�      5�      5�      :� 5�      $ 
MouseLeave��6   [�5�      �� 5�      .��5�      �� .��5�   "   �� $ 	#526F6FC1X�61   $ 0:0:0.1D�6@   $ windowmove_btn_color��6S   $ Color�6�   5�      5�      5�      :� 5�      $ MouseLeftButtonDown��6   [�5�      �� 5�      .��5�      �� .��5�   "   �� $ 	#7D6F316AX�61   $ 0:0:0.1D�6@   $ windowmove_btn_color��6S   $ Color�6�   5�      5�      5�      :� 5�      $ MouseLeftButtonUp��6   [�5�      �� 5�      .��5�      �� .��5�   "   �� $ 	#826F6FC1X�61   $ 0:0:0.1D�6@   $ windowmove_btn_color��6S   $ Color�6�   5�      5�      5     5     5     5     