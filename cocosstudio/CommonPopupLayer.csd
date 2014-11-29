<GameProjectFile>
  <PropertyGroup Type="Layer" Name="CommonPopupLayer" ID="9950e7e5-6b8e-406a-ad6d-a0a94b27e3bd" Version="2.0.2.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" CanEdit="False" FrameEvent="" ComboBoxIndex="1" ColorAngle="0.0000" ctype="PanelObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="640.0000" Y="960.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="Panel_mask" ActionTag="-1614460423" FrameEvent="" Tag="102" ObjectIndex="8" PrePositionEnabled="True" PreSizeEnable="True" TouchEnable="True" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" ctype="PanelObjectData">
            <Position X="320.0000" Y="480.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="960.0000" Y="1440.0000" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.5000" Y="1.5000" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="0" G="0" B="0" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </NodeObjectData>
          <NodeObjectData Name="Panel_main" ActionTag="-1694890317" FrameEvent="" Tag="28" ObjectIndex="5" PrePositionEnabled="True" PreSizeEnable="True" TouchEnable="True" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Enable="True" LeftEage="3" RightEage="3" TopEage="3" BottomEage="3" Scale9OriginX="3" Scale9OriginY="3" Scale9Width="10" Scale9Height="10" ctype="PanelObjectData">
            <Position X="320.0000" Y="480.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="576.0000" Y="576.0000" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="0.9000" Y="0.6000" />
            <Children>
              <NodeObjectData Name="Button_ok" ActionTag="-1892749685" FrameEvent="" Tag="29" ObjectIndex="2" PrePositionEnabled="True" TouchEnable="True" FontSize="32" ButtonText="OK" Scale9Enable="True" Scale9Width="46" Scale9Height="36" ctype="ButtonObjectData">
                <Position X="172.8000" Y="86.4000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="150.0000" Y="48.0000" />
                <PrePosition X="0.3000" Y="0.1500" />
                <PreSize X="0.2885" Y="0.0923" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" />
              </NodeObjectData>
              <NodeObjectData Name="Button_ng" ActionTag="-789818537" FrameEvent="" Tag="30" ObjectIndex="3" PrePositionEnabled="True" TouchEnable="True" FontSize="32" ButtonText="NG" Scale9Enable="True" Scale9Width="46" Scale9Height="36" ctype="ButtonObjectData">
                <Position X="403.2000" Y="86.4000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="150.0000" Y="48.0000" />
                <PrePosition X="0.7000" Y="0.1500" />
                <PreSize X="0.2885" Y="0.0923" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" />
              </NodeObjectData>
              <NodeObjectData Name="Text_title" ActionTag="-1357852434" FrameEvent="" Tag="31" ObjectIndex="3" PrePositionEnabled="True" FontSize="48" LabelText="クエスト中断（Test）" ctype="TextObjectData">
                <Position X="288.0000" Y="518.4000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="472.0000" Y="54.0000" />
                <PrePosition X="0.5000" Y="0.9000" />
                <PreSize X="0.0000" Y="0.0000" />
              </NodeObjectData>
              <NodeObjectData Name="Text_message" ActionTag="-2108754291" FrameEvent="" Tag="32" ObjectIndex="4" PrePositionEnabled="True" FontSize="26" LabelText="このクエストを中断しますか？&#xA;&#xA;中断した場合は、ダンジョンで手に入れた&#xA;持ち物はすべて失います。" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Bottom" ctype="TextObjectData">
                <Position X="288.0000" Y="432.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="493.0000" Y="124.0000" />
                <PrePosition X="0.5000" Y="0.7500" />
                <PreSize X="0.5673" Y="0.0885" />
              </NodeObjectData>
              <NodeObjectData Name="Text_caution" ActionTag="-2123115907" FrameEvent="" Tag="33" ObjectIndex="5" PrePositionEnabled="True" FontSize="20" LabelText="中断した場合に経験値は獲得出来ません。" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Bottom" ctype="TextObjectData">
                <Position X="288.0000" Y="201.6000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="1.0000" />
                <CColor A="255" R="250" G="255" B="0" />
                <Size X="380.0000" Y="23.0000" />
                <PrePosition X="0.5000" Y="0.3500" />
                <PreSize X="0.0000" Y="0.0000" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="ui/dot_waku.png" />
            <SingleColor A="255" R="0" G="0" B="0" />
            <FirstColor A="255" R="0" G="0" B="0" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </NodeObjectData>
        </Children>
        <SingleColor A="255" R="0" G="0" B="0" />
        <FirstColor A="255" R="0" G="0" B="0" />
        <EndColor A="255" R="255" G="255" B="255" />
        <ColorVector ScaleX="1.0000" ScaleY="0.0000" />
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>