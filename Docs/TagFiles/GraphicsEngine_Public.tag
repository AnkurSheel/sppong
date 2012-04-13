<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>Graphics::IDXBase</name>
    <filename>class_graphics_1_1_i_d_x_base.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VOnInitialization</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a2da57cda8fb47db3bd2d5fd3f70d205f</anchor>
      <arglist>(const HWND hWnd, const D3DCOLOR &amp;bkColor, const bool bFullScreen, const int iWidth, const int iHeight)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual HRESULT</type>
      <name>VOnResetDevice</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a6ff1da721209a99c5956332f9c59efbb</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual HRESULT</type>
      <name>VBeginRender</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a672e0f7da04c595fc30974dfe5339942</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VEndRender</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a81490bbf871175e073965257b97cb6f8</anchor>
      <arglist>(const HRESULT hr)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual LPDIRECT3DDEVICE9</type>
      <name>VGetDevice</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a9594b2ae572fa05cac77be940269c85f</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual HRESULT</type>
      <name>VIsAvailable</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a19a65fa8f771cb0e49b93b2249c36d6c</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VOnDestroy</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a2fe4370e2db37eede8107c838c32527a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>VToggleFullScreen</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>ac8ac1b35c6f5600e1c5940595653ad5d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GRAPHIC_API IDXBase *</type>
      <name>GetInstance</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a8f1d263d792f01d43a17761958324239</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
</tagfile>
