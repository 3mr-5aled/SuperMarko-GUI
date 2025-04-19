#pragma once
#include"MyForm1.h"
namespace SuperMarkoGUI {

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
	private: System::Windows::Forms::Panel^ pn_left_bar;
	protected:
	private: System::Windows::Forms::Panel^ pn_upper_bar;
	private: System::Windows::Forms::Panel^ pn_object_bar;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Button^ bt_edit_information;
	private: System::Windows::Forms::Panel^ pn_profile;




	private: System::Windows::Forms::Button^ bt_product;
	private: System::Windows::Forms::Button^ bt_order;
	private: System::Windows::Forms::Button^ bt_log_out;
	private: System::Windows::Forms::Button^ bt_exit;
	private: System::Windows::Forms::Button^ bt_minimized;





	private: System::Windows::Forms::Button^ bt_maximized;






	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pn_left_bar = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->bt_edit_information = (gcnew System::Windows::Forms::Button());
			this->bt_product = (gcnew System::Windows::Forms::Button());
			this->bt_order = (gcnew System::Windows::Forms::Button());
			this->bt_log_out = (gcnew System::Windows::Forms::Button());
			this->pn_profile = (gcnew System::Windows::Forms::Panel());
			this->pn_upper_bar = (gcnew System::Windows::Forms::Panel());
			this->bt_minimized = (gcnew System::Windows::Forms::Button());
			this->bt_maximized = (gcnew System::Windows::Forms::Button());
			this->bt_exit = (gcnew System::Windows::Forms::Button());
			this->pn_object_bar = (gcnew System::Windows::Forms::Panel());
			this->pn_left_bar->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->pn_upper_bar->SuspendLayout();
			this->SuspendLayout();
			// 
			// pn_left_bar
			// 
			this->pn_left_bar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_left_bar->Controls->Add(this->flowLayoutPanel1);
			this->pn_left_bar->Controls->Add(this->pn_profile);
			this->pn_left_bar->Dock = System::Windows::Forms::DockStyle::Left;
			this->pn_left_bar->Location = System::Drawing::Point(0, 0);
			this->pn_left_bar->Name = L"pn_left_bar";
			this->pn_left_bar->Size = System::Drawing::Size(262, 799);
			this->pn_left_bar->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->bt_edit_information);
			this->flowLayoutPanel1->Controls->Add(this->bt_product);
			this->flowLayoutPanel1->Controls->Add(this->bt_order);
			this->flowLayoutPanel1->Controls->Add(this->bt_log_out);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 169);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(262, 630);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// bt_edit_information
			// 
			this->bt_edit_information->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->bt_edit_information->CausesValidation = false;
			this->bt_edit_information->FlatAppearance->BorderSize = 0;
			this->bt_edit_information->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_edit_information->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bt_edit_information->ForeColor = System::Drawing::Color::White;
			this->bt_edit_information->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_edit_information.Image")));
			this->bt_edit_information->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->bt_edit_information->Location = System::Drawing::Point(3, 10);
			this->bt_edit_information->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			this->bt_edit_information->Name = L"bt_edit_information";
			this->bt_edit_information->Size = System::Drawing::Size(253, 95);
			this->bt_edit_information->TabIndex = 0;
			this->bt_edit_information->Text = L"Edit Information";
			this->bt_edit_information->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->bt_edit_information->UseVisualStyleBackColor = false;
			// 
			// bt_product
			// 
			this->bt_product->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->bt_product->CausesValidation = false;
			this->bt_product->FlatAppearance->BorderSize = 0;
			this->bt_product->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_product->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bt_product->ForeColor = System::Drawing::Color::White;
			this->bt_product->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_product.Image")));
			this->bt_product->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->bt_product->Location = System::Drawing::Point(3, 118);
			this->bt_product->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			this->bt_product->Name = L"bt_product";
			this->bt_product->Size = System::Drawing::Size(259, 95);
			this->bt_product->TabIndex = 1;
			this->bt_product->Text = L"Product";
			this->bt_product->UseVisualStyleBackColor = false;
			// 
			// bt_order
			// 
			this->bt_order->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->bt_order->CausesValidation = false;
			this->bt_order->FlatAppearance->BorderSize = 0;
			this->bt_order->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_order->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bt_order->ForeColor = System::Drawing::Color::White;
			this->bt_order->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_order.Image")));
			this->bt_order->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->bt_order->Location = System::Drawing::Point(3, 226);
			this->bt_order->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			this->bt_order->Name = L"bt_order";
			this->bt_order->Size = System::Drawing::Size(256, 95);
			this->bt_order->TabIndex = 2;
			this->bt_order->Text = L"Order";
			this->bt_order->UseVisualStyleBackColor = false;
			// 
			// bt_log_out
			// 
			this->bt_log_out->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->bt_log_out->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->bt_log_out->CausesValidation = false;
			this->bt_log_out->FlatAppearance->BorderSize = 0;
			this->bt_log_out->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_log_out->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bt_log_out->ForeColor = System::Drawing::Color::White;
			this->bt_log_out->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_log_out.Image")));
			this->bt_log_out->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->bt_log_out->Location = System::Drawing::Point(3, 529);
			this->bt_log_out->Margin = System::Windows::Forms::Padding(3, 205, 3, 3);
			this->bt_log_out->Name = L"bt_log_out";
			this->bt_log_out->Size = System::Drawing::Size(259, 101);
			this->bt_log_out->TabIndex = 3;
			this->bt_log_out->Text = L"Log out";
			this->bt_log_out->UseVisualStyleBackColor = false;
			this->bt_log_out->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// pn_profile
			// 
			this->pn_profile->Dock = System::Windows::Forms::DockStyle::Top;
			this->pn_profile->Location = System::Drawing::Point(0, 0);
			this->pn_profile->Name = L"pn_profile";
			this->pn_profile->Size = System::Drawing::Size(262, 169);
			this->pn_profile->TabIndex = 0;
			// 
			// pn_upper_bar
			// 
			this->pn_upper_bar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_upper_bar->Controls->Add(this->bt_minimized);
			this->pn_upper_bar->Controls->Add(this->bt_maximized);
			this->pn_upper_bar->Controls->Add(this->bt_exit);
			this->pn_upper_bar->Dock = System::Windows::Forms::DockStyle::Top;
			this->pn_upper_bar->Location = System::Drawing::Point(262, 0);
			this->pn_upper_bar->Name = L"pn_upper_bar";
			this->pn_upper_bar->Size = System::Drawing::Size(845, 100);
			this->pn_upper_bar->TabIndex = 1;
			// 
			// bt_minimized
			// 
			this->bt_minimized->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->bt_minimized->CausesValidation = false;
			this->bt_minimized->FlatAppearance->BorderSize = 0;
			this->bt_minimized->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_minimized->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_minimized.Image")));
			this->bt_minimized->Location = System::Drawing::Point(553, 12);
			this->bt_minimized->Name = L"bt_minimized";
			this->bt_minimized->Size = System::Drawing::Size(75, 73);
			this->bt_minimized->TabIndex = 2;
			this->bt_minimized->UseVisualStyleBackColor = true;
			this->bt_minimized->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// bt_maximized
			// 
			this->bt_maximized->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->bt_maximized->FlatAppearance->BorderSize = 0;
			this->bt_maximized->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_maximized->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_maximized.Image")));
			this->bt_maximized->Location = System::Drawing::Point(653, 3);
			this->bt_maximized->Name = L"bt_maximized";
			this->bt_maximized->Size = System::Drawing::Size(90, 91);
			this->bt_maximized->TabIndex = 1;
			this->bt_maximized->UseVisualStyleBackColor = true;
			this->bt_maximized->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// bt_exit
			// 
			this->bt_exit->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->bt_exit->FlatAppearance->BorderSize = 0;
			this->bt_exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->bt_exit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bt_exit.Image")));
			this->bt_exit->Location = System::Drawing::Point(749, 7);
			this->bt_exit->Name = L"bt_exit";
			this->bt_exit->Size = System::Drawing::Size(93, 82);
			this->bt_exit->TabIndex = 0;
			this->bt_exit->UseVisualStyleBackColor = true;
			this->bt_exit->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// pn_object_bar
			// 
			this->pn_object_bar->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_object_bar->Location = System::Drawing::Point(262, 100);
			this->pn_object_bar->Name = L"pn_object_bar";
			this->pn_object_bar->Size = System::Drawing::Size(845, 699);
			this->pn_object_bar->TabIndex = 2;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->ClientSize = System::Drawing::Size(1107, 799);
			this->Controls->Add(this->pn_object_bar);
			this->Controls->Add(this->pn_upper_bar);
			this->Controls->Add(this->pn_left_bar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Super Marko";
			this->pn_left_bar->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->pn_upper_bar->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		Environment::Exit(0);
	}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	if (this->WindowState == FormWindowState::Maximized)
	{
		this->WindowState = FormWindowState::Normal;
	}
	else
	{
		this->WindowState = FormWindowState::Maximized;
	}
}
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	this->WindowState = FormWindowState::Minimized;
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	MyForm1^ form1 = gcnew MyForm1;
	form1->Show();
	
}
};
}
