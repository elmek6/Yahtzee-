#include "MainForm.h"

	using namespace System;
	using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Yahtzee::MainForm MainForm;
	Application::Run(%MainForm);
}


	

/*
 
 #include "MyForm.h"

using namespace System;
using namespace System ::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	WindowsFormsC::MyForm form;
	Application::Run(%form);
}
 */