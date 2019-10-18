<GameFile>
  <PropertyGroup Name="Runner4" Type="Node" ID="54f8308b-9878-46a5-8621-493dbaeddacc" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="24" Speed="1.0000">
        <Timeline ActionTag="-743609442" Property="FileData">
          <TextureFrame FrameIndex="0" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_1.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="3" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_2.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="6" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_3.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="9" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_4.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="12" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_5.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="15" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_6.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="18" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_7.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="21" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_8.png" Plist="runner.plist" />
          </TextureFrame>
          <TextureFrame FrameIndex="24" Tween="False">
            <TextureFile Type="PlistSubImage" Path="triangle_1.png" Plist="runner.plist" />
          </TextureFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Node" Tag="16" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="body" ActionTag="-743609442" Tag="44" IconVisible="False" LeftMargin="-104.5000" RightMargin="-104.5000" TopMargin="-112.0000" BottomMargin="-112.0000" ctype="SpriteObjectData">
            <Size X="209.0000" Y="224.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="PlistSubImage" Path="triangle_1.png" Plist="runner.plist" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Normal" ActionTag="-1274866387" Tag="58" IconVisible="False" LeftMargin="-102.9600" RightMargin="-97.0400" TopMargin="-116.9100" BottomMargin="-83.0900" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="200.0000" Y="200.0000" />
            <Children>
              <AbstractNodeData Name="mouth" ActionTag="-495573665" Tag="60" IconVisible="False" LeftMargin="53.6554" RightMargin="111.3446" TopMargin="96.0518" BottomMargin="82.9482" ctype="SpriteObjectData">
                <Size X="35.0000" Y="21.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="71.1554" Y="93.4482" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3558" Y="0.4672" />
                <PreSize X="0.1750" Y="0.1050" />
                <FileData Type="PlistSubImage" Path="cmouth1.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="eye" ActionTag="1206046833" Tag="61" IconVisible="False" LeftMargin="35.5798" RightMargin="78.4202" TopMargin="42.7304" BottomMargin="108.2696" ctype="SpriteObjectData">
                <Size X="86.0000" Y="49.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="78.5798" Y="132.7696" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3929" Y="0.6638" />
                <PreSize X="0.4300" Y="0.2450" />
                <FileData Type="PlistSubImage" Path="eyes_1.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-102.9600" Y="-83.0900" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sad" ActionTag="472610667" VisibleForFrame="False" Tag="59" IconVisible="False" LeftMargin="-102.9600" RightMargin="-97.0400" TopMargin="-116.9100" BottomMargin="-83.0900" TouchEnable="True" ClipAble="False" BackColorAlpha="102" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="200.0000" Y="200.0000" />
            <Children>
              <AbstractNodeData Name="mouth" ActionTag="-974182451" Tag="62" IconVisible="False" LeftMargin="50.6574" RightMargin="103.3426" TopMargin="95.6466" BottomMargin="82.3534" ctype="SpriteObjectData">
                <Size X="46.0000" Y="22.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="73.6574" Y="93.3534" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="142" G="142" B="142" />
                <PrePosition X="0.3683" Y="0.4668" />
                <PreSize X="0.2300" Y="0.1100" />
                <FileData Type="PlistSubImage" Path="cmouth2.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="eye" ActionTag="-1620922619" Tag="63" IconVisible="False" LeftMargin="35.8510" RightMargin="78.1490" TopMargin="42.1224" BottomMargin="108.8776" ctype="SpriteObjectData">
                <Size X="86.0000" Y="49.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="78.8510" Y="133.3776" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.3943" Y="0.6669" />
                <PreSize X="0.4300" Y="0.2450" />
                <FileData Type="PlistSubImage" Path="eyes_3 - 1.png" Plist="runner.plist" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="-102.9600" Y="-83.0900" />
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