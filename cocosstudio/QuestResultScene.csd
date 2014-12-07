<GameProjectFile>
  <PropertyGroup Type="Scene" Name="QuestResultScene" ID="e61e97e0-d07b-4f5b-b2cb-f3ceb4e0dd0d" Version="2.0.2.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" CanEdit="False" FrameEvent="" ctype="SingleNodeObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="640.0000" Y="960.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="Sprite_back" ActionTag="781819731" Alpha="153" FrameEvent="" Tag="23" ObjectIndex="1" ctype="SpriteObjectData">
            <Position X="317.0000" Y="489.0000" />
            <Scale ScaleX="2.0000" ScaleY="2.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="640.0000" Y="480.0000" />
            <PrePosition X="0.4953" Y="0.5094" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="bg/ad_pass01_a.jpg" />
          </NodeObjectData>
          <NodeObjectData Name="Text_playMessage" ActionTag="-603945864" FrameEvent="" Tag="10" ObjectIndex="1" PrePositionEnabled="True" FontSize="36" LabelText="Sample Quest Clear  &#xA;24 F&#xA;&#xA;無事に最下層まで到達し、脱出した。" HorizontalAlignmentType="HT_Center" ctype="TextObjectData">
            <Position X="320.0000" Y="720.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="612.0000" Y="168.0000" />
            <PrePosition X="0.5000" Y="0.7500" />
            <PreSize X="0.9563" Y="0.1312" />
          </NodeObjectData>
          <NodeObjectData Name="Button_reward" ActionTag="-1190703508" FrameEvent="" Tag="27" ObjectIndex="2" PrePositionEnabled="True" TouchEnable="True" FontSize="20" ButtonText="報酬を確認する" Scale9Enable="True" LeftEage="20" RightEage="20" TopEage="20" BottomEage="20" Scale9OriginX="20" Scale9OriginY="20" Scale9Width="230" Scale9Height="37" ctype="ButtonObjectData">
            <Position X="160.0000" Y="192.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="220.0000" Y="60.0000" />
            <PrePosition X="0.2500" Y="0.2000" />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="250" G="250" B="250" />
            <DisabledFileData Type="Normal" Path="ui/button1_disable.png" />
            <PressedFileData Type="Normal" Path="ui/button1_press.png" />
            <NormalFileData Type="Normal" Path="ui/button1.png" />
          </NodeObjectData>
          <NodeObjectData Name="Button_log" ActionTag="-377550663" FrameEvent="" Tag="28" ObjectIndex="3" PrePositionEnabled="True" TouchEnable="True" FontSize="20" ButtonText="行動履歴を確認する" Scale9Enable="True" LeftEage="20" RightEage="20" TopEage="20" BottomEage="20" Scale9OriginX="20" Scale9OriginY="20" Scale9Width="230" Scale9Height="37" ctype="ButtonObjectData">
            <Position X="480.0000" Y="192.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="220.0000" Y="60.0000" />
            <PrePosition X="0.7500" Y="0.2000" />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="250" G="250" B="250" />
            <DisabledFileData Type="Normal" Path="ui/button1_disable.png" />
            <PressedFileData Type="Normal" Path="ui/button1_press.png" />
            <NormalFileData Type="Normal" Path="ui/button1.png" />
          </NodeObjectData>
          <NodeObjectData Name="Panel_message" ActionTag="-226860177" FrameEvent="" Tag="30" ObjectIndex="3" PrePositionEnabled="True" PreSizeEnable="True" TouchEnable="True" BackColorAlpha="192" ComboBoxIndex="1" ColorAngle="270.0000" Scale9Enable="True" LeftEage="3" RightEage="3" TopEage="3" BottomEage="3" Scale9OriginX="3" Scale9OriginY="3" Scale9Width="10" Scale9Height="10" ctype="PanelObjectData">
            <Position X="320.0000" Y="288.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="512.0000" Y="144.0000" />
            <PrePosition X="0.5000" Y="0.3000" />
            <PreSize X="0.8000" Y="0.1500" />
            <Children>
              <NodeObjectData Name="Label_message" ActionTag="-1255367181" FrameEvent="" Tag="31" ObjectIndex="1" PrePositionEnabled="True" FontSize="32" LabelText="aaaaaaaaaaaaaaaaaaa &#xA;aaaaaaaaaaaaaaaaaaa&#xA;0123456789012345678" IsCustomSize="True" TouchScaleChangeAble="True" ctype="TextObjectData">
                <Position X="153.6000" Y="129.6000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="340.0000" Y="120.0000" />
                <PrePosition X="0.3000" Y="0.9000" />
                <PreSize X="0.6641" Y="0.8333" />
              </NodeObjectData>
              <NodeObjectData Name="Sprite_actor" ActionTag="-1218448375" FrameEvent="" Tag="11" ObjectIndex="2" ctype="SpriteObjectData">
                <Position X="82.5000" Y="74.5000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="96.0000" Y="96.0000" />
                <PrePosition X="0.1611" Y="0.5174" />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="PlistSubImage" Path="actor_4_f_2_0.png" Plist="actor/4/actor_4_f_2.plist" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="ui/dot_waku.png" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="0" G="0" B="0" />
            <EndColor A="255" R="150" G="200" B="255" />
            <ColorVector ScaleX="0.0000" ScaleY="-1.0000" />
          </NodeObjectData>
          <NodeObjectData Name="__debug_header__" ActionTag="2111510257" FrameEvent="" Tag="26" ObjectIndex="2" PrePositionEnabled="True" BackColorAlpha="100" ComboBoxIndex="1" ColorAngle="270.0000" ctype="PanelObjectData">
            <Position X="0.0000" Y="960.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="1280.0000" Y="80.0000" />
            <PrePosition X="0.0000" Y="1.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="255" G="0" B="5" />
            <FirstColor A="255" R="255" G="0" B="5" />
            <EndColor A="255" R="150" G="200" B="255" />
            <ColorVector ScaleX="0.0000" ScaleY="-1.0000" />
          </NodeObjectData>
          <NodeObjectData Name="__debug_fotter__" ActionTag="1573713546" FrameEvent="" Tag="25" ObjectIndex="1" PrePositionEnabled="True" TouchEnable="True" BackColorAlpha="100" ComboBoxIndex="1" ColorAngle="270.0000" ctype="PanelObjectData">
            <Position X="0.0000" Y="0.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="1280.0000" Y="120.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="255" G="0" B="4" />
            <FirstColor A="255" R="255" G="0" B="4" />
            <EndColor A="255" R="150" G="200" B="255" />
            <ColorVector ScaleX="0.0000" ScaleY="-1.0000" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>