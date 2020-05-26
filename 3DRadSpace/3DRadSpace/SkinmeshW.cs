﻿using System;
using System.IO;
using System.Windows.Forms;
using _3DRadSpaceDll;
using Microsoft.Xna.Framework;

namespace _3DRadSpace
{
    public partial class SkinmeshW : Form
    {
        public GameObject Result;
        public SkinmeshW(Skinmesh sk)
        {
            InitializeComponent();
            textBox1.Text = sk.Name;
            checkBox1.Checked = sk.Enabled;
            textBox2.Text = sk.Resource;
            textBox3.Text = sk.Position.X.ToString("0.0",Program.CultureInfo);
            textBox4.Text = sk.Position.Y.ToString("0.0", Program.CultureInfo);
            textBox5.Text = sk.Position.Z.ToString("0.0", Program.CultureInfo);
            textBox8.Text = sk.Rotation.X.ToString("0.0", Program.CultureInfo);
            textBox7.Text = sk.Rotation.Y.ToString("0.0", Program.CultureInfo);
            textBox6.Text = sk.Rotation.Z.ToString("0.0", Program.CultureInfo);
            textBox11.Text = sk.Scale.X.ToString("0.0", Program.CultureInfo);
            textBox10.Text = sk.Scale.Y.ToString("0.0", Program.CultureInfo);
            textBox9.Text = sk.Scale.Z.ToString("0.0", Program.CultureInfo);
            textBox12.Text = sk.BoundingSphere.Radius.ToString("0.0", Program.CultureInfo);
            textBox13.Text = sk.BoundingBox.Min.X.ToString("0.0", Program.CultureInfo);
            textBox14.Text = sk.BoundingBox.Min.Y.ToString("0.0", Program.CultureInfo);
            textBox15.Text = sk.BoundingBox.Min.Z.ToString("0.0", Program.CultureInfo);
            textBox18.Text = sk.BoundingBox.Max.X.ToString("0.0", Program.CultureInfo);
            textBox17.Text = sk.BoundingBox.Max.Y.ToString("0.0", Program.CultureInfo);
            textBox16.Text = sk.BoundingBox.Max.Z.ToString("0.0", Program.CultureInfo);
        }
        public SkinmeshW()
        {
            InitializeComponent();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if(!File.Exists("Content\\"+textBox2.Text+".xnb"))
            {
                MessageBox.Show("The file: \n" + Path.GetFullPath("Content\\" + textBox2.Text + ".xnb") + " doesn't exist.", "Resource file not found.", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            DialogResult = DialogResult.OK;
            Skinmesh r = new Skinmesh(Editor.ValidateTextInput(textBox1.Text) , checkBox1.Checked, textBox2.Text,
                new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox3.Text),Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox4.Text),Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox5.Text), Program.CultureInfo))
               ,new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox8.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox7.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox6.Text), Program.CultureInfo))
               ,new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox11.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox10.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox9.Text), Program.CultureInfo))
                ,checkBox2.Checked,new BoundingBox(
                    new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox13.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox14.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox15.Text), Program.CultureInfo))
                    ,new Vector3(Convert.ToSingle(Editor.ValidateNumberTextInput(textBox18.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox17.Text), Program.CultureInfo), Convert.ToSingle(Editor.ValidateNumberTextInput(textBox16.Text), Program.CultureInfo)))
                ,new BoundingSphere(Vector3.Zero,Convert.ToSingle(Editor.ValidateNumberTextInput(textBox12.Text), Program.CultureInfo)));
            Result = r;
            Close();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            //open docs
        }

        private void button6_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            listBox2.Items.Clear();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int index = listBox1.SelectedIndex;
            listBox1.Items.RemoveAt(index);
            listBox2.Items.RemoveAt(index);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //open parameters wizard
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog openf = new OpenFileDialog()
            {
                Title = "Find a shader...",
                Filter = "Shaders (*.fx;*fxo)|*.fx;*.fxo)"
            };
            if( openf.ShowDialog() == DialogResult.OK)
            {

            }
            openf.Dispose();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if(radioButton1.Checked == true)
            {
                radioButton2.Checked = false;
                radioButton3.Checked = false;
            }
        }
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton2.Checked == true)
            {
                radioButton1.Checked = false;
                radioButton3.Checked = false;
            }
        }
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton3.Checked == true)
            {
                radioButton1.Checked = false;
                radioButton2.Checked = false;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //TODO: Add model viewer
        }
    }
}
