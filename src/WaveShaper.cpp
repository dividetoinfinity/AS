//**************************************************************************************
//WaveSahper module for VCV Rack by Alfredo Santamaria - AS - https://github.com/AScustomWorks/AS
//
//Code taken from HetrickCV plugins by Michael Hetrick https://github.com/mhetrick/hetrickcv
//**************************************************************************************
#include "AS.hpp"

#include "dsp/digital.hpp"

struct WaveShaper : Module {
	enum ParamIds {
		AMOUNT_PARAM,
		SCALE_PARAM,
		RANGE_PARAM,
		BYPASS_SWITCH,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT,
		AMOUNT_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		BYPASS_LED,
		NUM_LIGHTS
	};

	SchmittTrigger bypass_button_trig;
	bool fx_bypass = false;

	WaveShaper() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;

	json_t *toJson()override {
		json_t *rootJm = json_object();

		json_t *statesJ = json_array();
		
			json_t *bypassJ = json_boolean(fx_bypass);
			json_array_append_new(statesJ, bypassJ);
		
		json_object_set_new(rootJm, "as_FxBypass", statesJ);

		return rootJm;
	}

	void fromJson(json_t *rootJm)override {
		json_t *statesJ = json_object_get(rootJm, "as_FxBypass");
		
			json_t *bypassJ = json_array_get(statesJ, 0);

			fx_bypass = !!json_boolean_value(bypassJ);
		
	}

};


void WaveShaper::step() {

	if (bypass_button_trig.process(params[BYPASS_SWITCH].value)){
		fx_bypass = !fx_bypass;
	}
    lights[BYPASS_LED].value = fx_bypass ? 1.0 : 0.0;

	float input = inputs[INPUT].value;

	bool mode5V = (params[RANGE_PARAM].value == 0.0f);
    if(mode5V) input = clampf(input, -5.0f, 5.0f) * 0.2f;
	else input = clampf(input, -10.0f, 10.0f) * 0.1f;

	float shape = params[AMOUNT_PARAM].value + (inputs[AMOUNT_INPUT].value * params[SCALE_PARAM].value);
	shape = clampf(shape, -5.0f, 5.0f) * 0.2f;
	shape *= 0.99f;

	const float shapeB = (1.0 - shape) / (1.0 + shape);
	const float shapeA = (4.0 * shape) / ((1.0 - shape) * (1.0 + shape));

	float output = input * (shapeA + shapeB);
	output = output / ((std::abs(input) * shapeA) + shapeB);
	output *= 10.0f;
    //check for bypass switch status
	if (fx_bypass){
		 outputs[OUTPUT].value = inputs[INPUT].value;
	  }else{
		outputs[OUTPUT].value = output;
	  }
}

WaveShaperWidget::WaveShaperWidget() {
	WaveShaper *module = new WaveShaper();
	setModule(module);
	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/WaveShaper.svg")));
		addChild(panel);
	}
	//SCREWS
	addChild(createScrew<as_HexScrew>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<as_HexScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createScrew<as_HexScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createScrew<as_HexScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	//PARAMS
	addParam(createParam<as_KnobBlack>(Vec(26, 60), module, WaveShaper::AMOUNT_PARAM, -5.0, 5.0, 0.0));
	addParam(createParam<as_KnobBlack>(Vec(26, 125), module, WaveShaper::SCALE_PARAM, -1.0, 1.0, 1.0));
	//INPUTS
	addInput(createInput<as_PJ301MPort>(Vec(33, 180), module, WaveShaper::AMOUNT_INPUT));
	//RANGE SWITCH
	addParam(createParam<as_CKSSH>(Vec(33, 220), module, WaveShaper::RANGE_PARAM, 0.0, 1.0, 0.0));
    //BYPASS SWITCH
  	addParam(createParam<LEDBezel>(Vec(33, 260), module, WaveShaper::BYPASS_SWITCH , 0.0, 1.0, 0.0));
  	addChild(createLight<LedLight<RedLight>>(Vec(35.2, 262), module, WaveShaper::BYPASS_LED));
    //INS/OUTS
	addInput(createInput<as_PJ301MPort>(Vec(10, 310), module, WaveShaper::INPUT));
	addOutput(createOutput<as_PJ301MPort>(Vec(55, 310), module, WaveShaper::OUTPUT));

}
