using Engine3DRadSpace_VSExtension;
using EnvDTE;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.TemplateWizard;
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;

namespace _3DRadSpace_VSExtension 
{
	public class ProjectWizard : IWizard
	{
		public void BeforeOpeningFile(ProjectItem projectItem)
		{
		}

		public void ProjectFinishedGenerating(Project project)
		{
		}

		public void ProjectItemFinishedGenerating(ProjectItem projectItem)
		{
		}

		public void RunFinished()
		{
		}

		public void RunStarted(object automationObject,
			Dictionary<string, string> replacementsDictionary,
			WizardRunKind runKind, object[] customParams)
		{
			ThreadHelper.ThrowIfNotOnUIThread();

			var shell = (IVsShell)Package.GetGlobalService(typeof(SVsShell));
			Guid packageGuid = new Guid(Engine3DRadSpace_VSExtensionPackage.PackageGuidString);
			shell.LoadPackage(ref packageGuid, out IVsPackage vsPackage);
			var package = (Engine3DRadSpace_VSExtensionPackage)vsPackage;
			var options = (ExtensionSettings)package.GetDialogPage(typeof(ExtensionSettings));

			if(string.IsNullOrEmpty(options.InstallPath) || !Directory.Exists(options.InstallPath))
			{
				FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();

				while (true)
				{
					folderBrowserDialog.Description = "Select the folder where 3DRadSpace is located.";
					folderBrowserDialog.ShowNewFolderButton = false;
					folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;

					if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
					{
						string editorFilePath = Path.Combine(folderBrowserDialog.SelectedPath, "3DRadSpace.Editor.exe");

                        if (!File.Exists(editorFilePath))
						{
							DialogResult r = MessageBox.Show("The selected folder isn't an 3DRadSpace installation path", "Invalid path", MessageBoxButtons.OKCancel, MessageBoxIcon.Error);
							if (r == DialogResult.Cancel)
							{
								folderBrowserDialog.Dispose();
								throw new WizardCancelledException("The installation folder was not selected", new FileNotFoundException("", editorFilePath));
							}	
						}

						options.InstallPath = folderBrowserDialog.SelectedPath;

						folderBrowserDialog.Dispose();
						break;
					}
				}
			}

			replacementsDictionary["$InstallDir$"] = options.InstallPath;
		}

		public bool ShouldAddProjectItem(string filePath)
		{
			return true;
		}
	}
}
