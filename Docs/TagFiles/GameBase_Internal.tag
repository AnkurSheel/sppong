<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>GameBase::IMainWindow</name>
    <filename>class_game_base_1_1_i_main_window.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual GAMEBASE_API HWND</type>
      <name>VOnInitialization</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>a008e0638dfd37d195f6887ef3d33059b</anchor>
      <arglist>(const HINSTANCE &amp;hInstance, const int &amp;nCmdShow, IBaseApp *const pGame, const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual GAMEBASE_API void</type>
      <name>VOnDestroy</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>afe7db58a887fbd1cb5740741f272dd9e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual GAMEBASE_API void</type>
      <name>VToggleFullScreen</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>af6afc37f85594dc960628b574b1c15da</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static GAMEBASE_API IMainWindow *</type>
      <name>GetInstance</name>
      <anchorfile>class_game_base_1_1_i_main_window.html</anchorfile>
      <anchor>a4090ba165e3ba80a9a3d6949ba4fb3f3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GameBase::cMainWindow</name>
    <filename>class_game_base_1_1c_main_window.html</filename>
    <base>GameBase::IMainWindow</base>
    <member kind="function">
      <type>HWND</type>
      <name>VOnInitialization</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a35bfba0963cb73fe59f6127d3ca16d45</anchor>
      <arglist>(const HINSTANCE &amp;hInstance, const int &amp;nCmdShow, IBaseApp *const pGame, const bool bFullScreen, const int iFullScreenWidth, const int iFullScreenHeight)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VOnDestroy</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a3eb0aff8ae2fecf8081a40dc31015352</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VToggleFullScreen</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a332eb3c53a163519c8063d8ed920d0cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static cMainWindow *</type>
      <name>Create</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>aaa858088a4c2203b36fa917d11798d4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RegisterWin</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>af22ea267f5a12c3f297a1d0af300b4bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>CreateMyWindow</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a0957f015bad2322bb518c96bfb4968da</anchor>
      <arglist>(const int &amp;nCmdShow, const Base::cString &amp;lpWindowTitle)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>LRESULT CALLBACK</type>
      <name>WndProc</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a34c0302fa66b64a61aaf2830ad28b134</anchor>
      <arglist>(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnWindowCreated</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a21c2d81624366c2264239b7550552b51</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnWindowDestroyed</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a706622ac9bba08ed54be1c8afb0eac75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetDisplayResolution</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>ac7c58c9c7715cfee9477b378e4cf21dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static LRESULT CALLBACK</type>
      <name>StaticWndProc</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>ae300f890e0792e50e0311d7f3b8e8614</anchor>
      <arglist>(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const DWORD</type>
      <name>m_kdwFullScreenStyle</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a49288199090e86f10f71a9ffcac9543a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const DWORD</type>
      <name>m_kdwWindowedStyle</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a6fd476492260b48c4e6f105e817b5325</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>WINDOWPLACEMENT</type>
      <name>m_wp</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>add15048ac50c58ddbe931b67988bd4b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_bFullScreen</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a86504cf9c5cf45b9404ca1983fa9e8ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>HWND</type>
      <name>m_Hwnd</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a904ace28c221002cdcb529a31731601f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>HINSTANCE</type>
      <name>m_hInstance</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a5f75deceeb79ada4746379fa9d092aeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iFullScreenWidth</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a1e261fbb35c950b3b0259dad8f84c42c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>m_iFullScreenHeight</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>a20ed6502157253203d4d1c951290d7ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>IBaseApp *</type>
      <name>m_pGame</name>
      <anchorfile>class_game_base_1_1c_main_window.html</anchorfile>
      <anchor>aa599ab9886823365c4ce532a58c5150c</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
