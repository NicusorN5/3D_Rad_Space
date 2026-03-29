using Microsoft.VisualStudio.Shell;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpace_VSExtension
{
	internal class ExtensionSettings : DialogPage
	{
		private string _installPath = null;

		[Category("General")]
		[DisplayName("3DRadSpace Installation Path")]
		[Description("Path to the 3DRadSpace installation.")]
		public string InstallPath
		{
			get => _installPath;
			set => _installPath = value;
		}
	}
}
