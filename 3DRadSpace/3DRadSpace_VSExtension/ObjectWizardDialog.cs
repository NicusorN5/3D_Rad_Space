using Microsoft.VisualStudio.PlatformUI;
using System.Windows;

namespace _3DRadSpace_VSExtension
{
	public partial class ObjectWizardDialog : DialogWindow
	{
		public ObjectWizardDialog(string className)
		{
			InitializeComponent();
			ClassNameBox.Text = className;
		}

		public string ClassName
		{
			get { return ClassNameBox.Text; }
		}

		public string BaseClass
		{
			get { return BaseClassComboBox.Text; }
		}

		public void ConfirmObj(object sender, RoutedEventArgs e)
		{
			DialogResult = true;
			Close();
		}
	}
}
