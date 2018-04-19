#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <climits>
#include <string>
#include <sstream>

using namespace std;

int const CMax = 100;

namespace ND3 {

	struct Autikai {
		int Nr;
		double ilgis;
		int sustot;
		int reisai;
	};

	bool operator <(const Autikai &a, const Autikai &b) {
		return a.sustot < b.sustot;
	}


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;


	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(88, 76);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(92, 36);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Vykdyti";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(40, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(203, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Áveskite L reikðmæ ir paspauskite mygtukà";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(88, 36);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(92, 20);
			this->textBox1->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 347);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(100, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Maþiausi reisai:";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(15, 118);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(258, 214);
			this->richTextBox1->TabIndex = 6;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(297, 381);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		Autikai A[CMax];
		Autikai R[CMax]; //R= Atrusiuoti duomenys
		int kiekis = 0, L, kiekis2 = 0, nr, maz = INT_MAX;
		int temp1, temp3, temp4;
		double temp2;
		bool isGood = true;
		ifstream IsF("Duomenys.txt");
		ofstream YF("Rezultatai.txt");

		//Nuskaitomi duomenys
		L = Convert::ToInt32(textBox1->Text);
		YF << "Pradiniai duomenys: " << endl;
		YF << "---------------------------" << endl;
		while (!IsF.eof())
		{
			IsF >> A[kiekis].Nr >> A[kiekis].ilgis >> A[kiekis].sustot >> A[kiekis].reisai;
			if (isdigit(A[kiekis].Nr) || isdigit(A[kiekis].ilgis) || isdigit(A[kiekis].sustot) || isdigit(A[kiekis].reisai) || 
				A[kiekis].Nr > 0 || A[kiekis].ilgis > 0 || A[kiekis].sustot > 0 || A[kiekis].reisai > 0)
				isGood = true;
			else isGood = false;
			kiekis++;
		}
		YF << "---------------------------" << endl;

		if (isGood == true)
		{
			for (int i = 0; i < kiekis; i++)
			{
				YF << "| " << setw(3) << left << A[kiekis].Nr << " | " << setw(3) << left << A[kiekis].ilgis << " | " << setw(3) << left << A[kiekis].sustot
					<< " | " << setw(3) << left << A[kiekis].reisai << " |" << endl;
			}
			//Atrinkami duomenys
			for (int i = 0; i < kiekis; i++)
				if (L < A[i].ilgis)
				{
					R[kiekis2] = A[i];
					kiekis2++;
				}

			//Rusiavimas;
			sort(R, R + kiekis2);
			YF << endl;
			YF << "Atrinkti duomenys ir surusuoti: " << endl;
			YF << "---------------------------" << endl;
			for (int i = 0; i < kiekis2; i++)
			{
				for (int j = i + 1; j < kiekis2; j++)
					if (R[i].sustot == R[j].sustot)
					{
						if (R[i].ilgis >= R[j].ilgis)
						{
							temp1 = R[i].Nr;
							temp2 = R[i].ilgis;
							temp3 = R[i].sustot;
							temp4 = R[i].reisai;
							R[i] = R[j];
							R[j].Nr = temp1;
							R[j].ilgis = temp2;
							R[j].sustot = temp3;
							R[j].reisai = temp4;
						}
					}
				YF << "| " << setw(3) << R[i].Nr << " | " << setw(3) << R[i].ilgis << " | " << setw(3) << R[i].sustot << " | " << setw(3) << R[i].reisai << " |" << endl;

			}
			YF << "---------------------------" << endl;

			//Maziausias
			for (int i = 0; i < kiekis2; i++)
				if (maz > R[i].reisai)
					maz = R[i].reisai;

			YF << "Maziausiu reisu per diena autobusu numeriai: ";
			for (int i = 0; i < kiekis2; i++)
				if (maz == R[i].reisai) {
					YF << R[i].Nr << " ";
					this->label2->Text = this->label2->Text + R[i].Nr + " ";
				}
			ifstream fin("Rezultatai.txt");
			std::stringstream buffer;
			buffer << fin.rdbuf();
			string temp = buffer.str();
			this->richTextBox1->Text = gcnew String(temp.c_str());
			label1->Text = "Programa Suveike";
		}
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}