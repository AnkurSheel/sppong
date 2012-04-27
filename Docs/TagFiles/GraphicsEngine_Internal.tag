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
      <type>virtual LPDIRECT3DDEVICE9</type>
      <name>VGetDevice</name>
      <anchorfile>class_graphics_1_1_i_d_x_base.html</anchorfile>
      <anchor>a9594b2ae572fa05cac77be940269c85f</anchor>
      <arglist>() const =0</arglist>
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
      <anchor>aa0c9bc1b1560d96df0e9d3e320295bc3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Graphics::cDXBase</name>
    <filename>class_graphics_1_1c_d_x_base.html</filename>
    <base>Graphics::IDXBase</base>
    <member kind="function" static="yes">
      <type>static cDXBase *</type>
      <name>Create</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a1646f4fcef6eace57ee70afda8574828</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VOnInitialization</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a454940a5d6043064c902830271f3ec9b</anchor>
      <arglist>(const HWND hWnd, const D3DCOLOR &amp;bkColor, const bool bFullScreen, const int iWidth, const int iHeight)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>HRESULT</type>
      <name>VOnResetDevice</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a05fab02d36a5338d19c20d615a176899</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>HRESULT</type>
      <name>VBeginRender</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a92439bf851448b0bfdfc06be14aec3be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VEndRender</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ae0b249eb178b17e6d0fc7eedebf52672</anchor>
      <arglist>(const HRESULT hr)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>LPDIRECT3DDEVICE9</type>
      <name>VGetDevice</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aea913cd77db14df6bbbb4a5953f07ee4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>HRESULT</type>
      <name>VIsAvailable</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ae14ed7a1fdc7fe52a4086cd3519382f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VOnDestroy</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a958f88e0050f0cc138f736139cf3feae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>VToggleFullScreen</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a9a76303a1d03a6a203be3ebf10969dcb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>DirectxInit</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a2e2c2517ad3295da0ca4f90db98e8175</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CreateDirectxDevice</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aff576a33547b8f91f43e2a911af2a7e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetParameters</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a2b3308b583640117d88ea1a60de24c94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Cleanup</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a60ad196fda78a302b855f181adff68d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>LPDIRECT3D9</type>
      <name>m_pD3D</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a915212f4c00120e05c4eadf520ea8eb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>LPDIRECT3DDEVICE9</type>
      <name>m_pd3dDevice</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aa5d2e2cca6d9675c2782f0db76ada675</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DCAPS9</type>
      <name>m_Caps</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a2951d5a95bd12dac169bed879e285b7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DCOLOR</type>
      <name>m_BkColor</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ab569b18d6fa69cfb702d208c2c6b92c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>HWND</type>
      <name>m_Hwnd</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>abf60d75244952a142cd8b3bb05db6266</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DPRESENT_PARAMETERS</type>
      <name>m_d3dpp</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a861fc1d28924b21c6dcfb0a8f3dbe542</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iWidth</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>aea1425b0eae506c830b9a6cfa33c8a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iHeight</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>ab55c0129f8ace3914b6199053c6fd118</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>D3DDISPLAYMODE</type>
      <name>m_displayMode</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a017eff385821a8b1ae8b2737dff06677</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bFullScreen</name>
      <anchorfile>class_graphics_1_1c_d_x_base.html</anchorfile>
      <anchor>a533e574f90c165ea21e972d36cff6059</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
