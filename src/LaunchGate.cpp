//**************************************************************************************
//LaunchGate module for VCV Rack by Alfredo Santamaria - AS - https://github.com/AScustomWorks/AS
//
//Code adapted from Dual Counter - VCV Module, Strum 2017
//**************************************************************************************

#include "AS.hpp"

#include "dsp/digital.hpp"

#include <sstream>
#include <iomanip>

struct LaunchGate : Module {
	enum ParamIds {
    RST_BUTTON1,
    COUNT_NUM_PARAM_1,
    RST_BUTTON2,
    COUNT_NUM_PARAM_2,
		NUM_PARAMS
	};  
	enum InputIds {
    INPUT_1,
    CLK_IN_1,
    RESET_IN_1,
    INPUT_2,
    CLK_IN_2,
    RESET_IN_2, 
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_1,
    OUTPUT_2,
    OUTPUT_3,    
		NUM_OUTPUTS
	};
    enum LightIds {
		RESET_LIGHT1,
		RESET_LIGHT2,
		NUM_LIGHTS
	};

    SchmittTrigger clock_trigger_1;
    SchmittTrigger reset_trigger_1;
    SchmittTrigger reset_ext_trigger_1;
    int count_limit1 = 1;
    int count1 = 0;
    SchmittTrigger clock_trigger_2;
    SchmittTrigger reset_trigger_2;
    SchmittTrigger reset_ext_trigger_2;
    int count_limit_2 = 1;
    int count_2 = 0;
 
    const float lightLambda = 0.075;

    float resetLight1 = 0.0;
    float resetLight2 = 0.0;

    bool gate1_open= false;
    bool gate2_open= false;

    LaunchGate() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {

    }

  void reset() override {
    
    count_limit1 = 1;
    count1 = 0;
    count_limit_2 = 1;
    count_2 = 0;
    gate1_open= false;
    gate2_open= false;

  }

	void step() override;

};


void LaunchGate::step(){

  count_limit1 = round(params[COUNT_NUM_PARAM_1].value);
  count_limit_2 = round(params[COUNT_NUM_PARAM_2].value);

  bool reset1 = false;
  bool reset_2 = false;
  ///////////// counter 1
  if (reset_trigger_1.process(params[RST_BUTTON1].value)){
      reset1 = true;
      count1 = 0;
      gate1_open=false;
      resetLight1 = 1.0;

  }
  if (reset_ext_trigger_1.process(inputs[RESET_IN_1].value)){
      reset1 = true;
      count1 = 0;
      gate1_open = false;
      resetLight1 = 1.0;

  } 

  resetLight1 -= resetLight1 / lightLambda / engineGetSampleRate();
  lights[RESET_LIGHT1].value = resetLight1;

  if (reset1 == false){
		if (clock_trigger_1.process(inputs[CLK_IN_1].value) && count1 <= count_limit1){
      if (!gate1_open){
					count1++;
      }
    }
  }
  if (count1 == count_limit1){
      gate1_open = true;
  }
  if (gate1_open){
      outputs[OUTPUT_1].value = inputs[INPUT_1].value;
  }else{
    outputs[OUTPUT_1].value = 0;
  }
  ///////////// counter 2
  if (reset_trigger_2.process(params[RST_BUTTON2].value)){
    reset_2 = true;
    count_2 = 0;
    gate2_open=false;
    resetLight2 = 1.0;
  }
  if (reset_ext_trigger_2.process(inputs[RESET_IN_2].value)){
    reset_2 = true;
    count_2 = 0;
    gate2_open=false;
    resetLight2 = 1.0;
  } 
  resetLight2 -= resetLight2 / lightLambda / engineGetSampleRate();
  lights[RESET_LIGHT2].value = resetLight2;

  if (reset_2 == false){
		if (clock_trigger_2.process(inputs[CLK_IN_2].value) && count_2 <= count_limit_2){
      if (!gate2_open){
					count_2++;
      }
    }
  }
  if (count_2 == count_limit_2){
      gate2_open = true;
  }
  if (gate2_open){
      outputs[OUTPUT_2].value = inputs[INPUT_2].value;
  }else{
    outputs[OUTPUT_2].value = 0;
  }

}

///////////////////////////////////
struct NumberDisplayWidget : TransparentWidget {

  int *value;
  std::shared_ptr<Font> font;

  NumberDisplayWidget() {
    font = Font::load(assetPlugin(plugin, "res/Segment7Standard.ttf"));
  };

  void draw(NVGcontext *vg) override
  {
    // Background
    NVGcolor backgroundColor = nvgRGB(0x20, 0x20, 0x20);
    NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
    nvgBeginPath(vg);
    nvgRoundedRect(vg, 0.0, 0.0, box.size.x, box.size.y, 4.0);
    nvgFillColor(vg, backgroundColor);
    nvgFill(vg);
    nvgStrokeWidth(vg, 1.0);
    nvgStrokeColor(vg, borderColor);
    nvgStroke(vg);    
    // text 
    nvgFontSize(vg, 18);
    nvgFontFaceId(vg, font->handle);
    nvgTextLetterSpacing(vg, 2.5);

    std::stringstream to_display;   
    to_display << std::right  << std::setw(2) << *value;

    Vec textPos = Vec(4.0f, 17.0f); 

    NVGcolor textColor = nvgRGB(0xdf, 0xd2, 0x2c);
    nvgFillColor(vg, nvgTransRGBA(textColor, 16));
    nvgText(vg, textPos.x, textPos.y, "~~", NULL);

    textColor = nvgRGB(0xda, 0xe9, 0x29);
    nvgFillColor(vg, nvgTransRGBA(textColor, 16));
    nvgText(vg, textPos.x, textPos.y, "\\\\", NULL);

    textColor = nvgRGB(0xf0, 0x00, 0x00);
    nvgFillColor(vg, textColor);
    nvgText(vg, textPos.x, textPos.y, to_display.str().c_str(), NULL);
  }
};
////////////////////////////////////


LaunchGateWidget::LaunchGateWidget() {
	LaunchGate *module = new LaunchGate();
	setModule(module);
	//box.size = Vec(15*4, 380);
  	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);
  
	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin,"res/LaunchGate.svg")));
		addChild(panel);
	}
  
 //SCREWS
	addChild(createScrew<as_HexScrew>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<as_HexScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createScrew<as_HexScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createScrew<as_HexScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  // counter 1
  //COUNT DISPLAY
    NumberDisplayWidget *display1 = new NumberDisplayWidget();
    display1->box.pos = Vec(10,50);
    display1->box.size = Vec(30, 20);
    display1->value = &module->count1;
    addChild(display1);
  //LaunchGate DISPLAY  
    NumberDisplayWidget *display2 = new NumberDisplayWidget();
    display2->box.pos = Vec(50,50);
    display2->box.size = Vec(30, 20);
    display2->value = &module->count_limit1;
    addChild(display2);

   int group_offset = 160;

    addParam(createParam<LEDBezel>(Vec(11, 82), module, LaunchGate::RST_BUTTON1 , 0.0, 1.0, 0.0));
    addChild(createLight<LedLight<RedLight>>(Vec(11+2.2, 82+2.3), module, LaunchGate::RESET_LIGHT1));

    addParam(createParam<as_KnobBlack>(Vec(43, 73), module, LaunchGate::COUNT_NUM_PARAM_1, 1.0, 64.0, 1.0)); 

    addInput(createInput<as_PJ301MPort>(Vec(10, 125), module, LaunchGate::RESET_IN_1));
    addInput(createInput<as_PJ301MPort>(Vec(55, 125), module, LaunchGate::CLK_IN_1));

    addInput(createInput<as_PJ301MPort>(Vec(10, 170), module, LaunchGate::INPUT_1));
    addOutput(createOutput<as_PJ301MPort>(Vec(55, 170), module, LaunchGate::OUTPUT_1));
  
  // counter 2
  //COUNT DISPLAY
    NumberDisplayWidget *display3 = new NumberDisplayWidget();
    display3->box.pos = Vec(10,50 + group_offset);
    display3->box.size = Vec(30, 20);
    display3->value = &module->count_2;
    addChild(display3);
  //LaunchGate DISPLAY  
    NumberDisplayWidget *display4 = new NumberDisplayWidget();
    display4->box.pos = Vec(50,50 + group_offset);
    display4->box.size = Vec(30, 20);
    display4->value = &module->count_limit_2;
    addChild(display4);

    addParam(createParam<LEDBezel>(Vec(11, 82+ group_offset), module, LaunchGate::RST_BUTTON2 , 0.0, 1.0, 0.0));
    addChild(createLight<LedLight<RedLight>>(Vec(11+2.2, 82+2.3+ group_offset), module, LaunchGate::RESET_LIGHT2));

    addParam(createParam<as_KnobBlack>(Vec(43, 73 + group_offset), module, LaunchGate::COUNT_NUM_PARAM_2, 1.0, 64.0, 1.0)); 

    addInput(createInput<as_PJ301MPort>(Vec(10, 125 + group_offset), module, LaunchGate::RESET_IN_2));
    addInput(createInput<as_PJ301MPort>(Vec(55, 125 + group_offset), module, LaunchGate::CLK_IN_2));

    addInput(createInput<as_PJ301MPort>(Vec(10, 170 + group_offset), module, LaunchGate::INPUT_2));
    addOutput(createOutput<as_PJ301MPort>(Vec(55, 170 + group_offset), module, LaunchGate::OUTPUT_2));
 
}
