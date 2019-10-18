<GameFile>
  <PropertyGroup Name="Runner2" Type="Node" ID="de9dfeb1-c4a1-49d0-a0ca-56f9253451c7" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="24" Speed="1.0000">
        <Timeline ActionTag="-1351959077" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_1.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_2.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="6" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_3.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="9" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_4.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="12" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_5.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_6.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="18" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_7.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="21" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_8.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="24" Tween="False">
            <TextureFile Type="PlistSubImage" Path="circle_1.png" Plist="runner.plist" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Node" Tag="13" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="body" ActionTag="-1351959077" Tag="30" IconVisible="False" LeftMargin="-107.0000" RightMargin="-107.0000" TopMargin="-101.5000" BottomMargin="-101.5000" ctype="SpriteObjectData">
            <Size X="214.0000" Y="203.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="circle_1.png" Plist="runner.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Normal" ActionTag="2143162077" Tag="49" IconVisible="False" LeftMargin="-90.1600" RightMargin="-109.8400" TopMargin="-122.1400" BottomMargin="-77.8600" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="200.0000" Y="200.0000" />
            <Children>
              <AbstractNodeData Name="mouth" ActionTag="-233997833" Tag="47" IconVisible="False" LeftMargin="58.0229" RightMargin="106.9771" TopMargin="96.6308" BottomMargin="82.3692" ctype="SpriteObjectData">
                <Size X="35.0000" Y="21.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="75.5229" Y="92.8692" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3776" Y="0.4643" />
                <PreSize X="0.1750" Y="0.1050" />
                <FileData Type="PlistSubImage" Path="cmouth1.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="eye" ActionTag="-1112818659" Tag="45" IconVisible="False" LeftMargin="40.0617" RightMargin="73.9383" TopMargin="41.2756" BottomMargin="109.7244" ctype="SpriteObjectData">
                <Size X="86.0000" Y="49.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="83.0617" Y="134.2244" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4153" Y="0.6711" />
                <PreSize X="0.4300" Y="0.2450" />
                <FileData Type="PlistSubImage" Path="eyes_1.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-90.1600" Y="-77.8600" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sad" ActionTag="-290043201" VisibleForFrame="False" Tag="50" IconVisible="False" LeftMargin="-90.1600" RightMargin="-109.8400" TopMargin="-122.1400" BottomMargin="-77.8600" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="200.0000" Y="200.0000" />
            <Children>
              <AbstractNodeData Name="eye" ActionTag="-1407871361" Tag="51" IconVisible="False" LeftMargin="40.1938" RightMargin="73.8062" TopMargin="40.8630" BottomMargin="110.1370" ctype="SpriteObjectData">
                <Size X="86.0000" Y="49.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="83.1938" Y="134.6370" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.4160" Y="0.6732" />
                <PreSize X="0.4300" Y="0.2450" />
                <FileData Type="PlistSubImage" Path="eyes_3 - 1.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="mouth" ActionTag="131801200" Tag="48" IconVisible="False" LeftMargin="53.9555" RightMargin="100.0445" TopMargin="96.7295" BottomMargin="81.2705" ctype="SpriteObjectData">
                <Size X="46.0000" Y="22.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="76.9555" Y="92.2705" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="142" G="142" B="142" />
                <PrePosition X="0.3848" Y="0.4614" />
                <PreSize X="0.2300" Y="0.1100" />
                <FileData Type="PlistSubImage" Path="cmouth2.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-90.1600" Y="-77.8600" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>