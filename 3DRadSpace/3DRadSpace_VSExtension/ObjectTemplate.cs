using EnvDTE;
using Microsoft.VisualStudio.TemplateWizard;
using System;
using System.Collections.Generic;

namespace _3DRadSpace_VSExtension
{
	public class ObjectTemplate : IWizard
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
			ObjectWizardDialog dialog = new ObjectWizardDialog(replacementsDictionary["$safeitemname$"]);
			if(dialog.ShowModal() != true)
			{
				throw new WizardCancelledException();
			}

			replacementsDictionary["$base$"] = dialog.BaseClass;
			replacementsDictionary["$className$"] = dialog.ClassName;

			switch (dialog.BaseClass)
			{
				case "IObject3D":
					replacementsDictionary["$drawDeclaration$"] = "void Draw3D() override;";
					replacementsDictionary["$drawImplementation$"] = "void " + dialog.ClassName + "::Draw3D()\r\n{\r\n\t//Add your own 3D drawing logic\r\n}";
					break;
				case "IObject2D":
					replacementsDictionary["$drawDeclaration$"] = "void Draw2D() override;";
					replacementsDictionary["$drawImplementation$"] = "void " + dialog.ClassName + "::Draw2D()\r\n{\r\n\t//Add your own 2D drawing logic\r\n}";
					break;
				default:
					replacementsDictionary["$drawDeclaration$"] = "";
					replacementsDictionary["$drawImplementation$"] = "";
					break;
			}

			Guid guid = Guid.NewGuid();

			replacementsDictionary["$guid$"] = guid.ToString("X");
			replacementsDictionary["$guidText$"] = guid.ToString("B").ToUpper();
		}

		public bool ShouldAddProjectItem(string filePath)
		{
			return true;
		}
	}
}
