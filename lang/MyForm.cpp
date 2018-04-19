#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

int main(char* args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ND3::MyForm form;
	Application::Run(%form);
}