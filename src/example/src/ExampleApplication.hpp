#pragma once
#include <lafez/Application.hpp>
#include <lafez/core/lafez_layer.hpp>

class ExampleApplication : public Lafez::Application {
public:
	ExampleApplication();
	~ExampleApplication();

	void startUp() override;
	void run() override;
	void shutDown() override;
private:
	Lafez::LayerStack mLayerStack;
	Lafez::DisposeBag mDisposeBag;
};