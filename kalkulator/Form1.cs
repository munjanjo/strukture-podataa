namespace kalkulator
{
    public partial class Form1 : Form
    {

        private decimal valueFirst = 0.0m;
        private decimal valueSecond = 0.0m;
        private decimal Result = 0.0m;
        private string operators = "+";
        public Form1()
        {
            InitializeComponent();
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (!textBox1.Text.Contains(","))
            {
                textBox1.Text += ",";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "7";

            }
            else
            {
                textBox1.Text += "7";
            }

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "4";

            }
            else
            {
                textBox1.Text += "4";
            }
        }

        private void zeroBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "0";

            }
            else
            {
                textBox1.Text += "0";
            }
        }

        private void oneBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "1";

            }
            else
            {
                textBox1.Text += "1";
            }
        }

        private void TwoBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "2";

            }
            else
            {
                textBox1.Text += "2";
            }
        }

        private void ThreeBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "3";

            }
            else
            {
                textBox1.Text += "3";
            }
        }

        private void FiveBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "5";

            }
            else
            {
                textBox1.Text += "5";
            }
        }

        private void SixBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "6";

            }
            else
            {
                textBox1.Text += "6";
            }
        }

        private void EightBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "8";

            }
            else
            {
                textBox1.Text += "8";
            }
        }

        private void NineBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "9";

            }
            else
            {
                textBox1.Text += "9";
            }
        }

        private void MinusBtn_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "0")
            {
                textBox1.Text = "-";

            }
            else if (textBox1.Text == "")
            {
                textBox1.Text = "-";

            }
            else
            {
                valueFirst = decimal.Parse(textBox1.Text);
                textBox1.Clear();
                operators = "-";
            }
        }

        private void plusBtn_Click(object sender, EventArgs e)
        {
            valueFirst = decimal.Parse(textBox1.Text);
            textBox1.Clear();
            operators = "+";
        }

        private void divideBtn_Click(object sender, EventArgs e)
        {
            valueFirst = decimal.Parse(textBox1.Text);
            textBox1.Clear();
            operators = "/";
        }

        private void multiplyBtn_Click(object sender, EventArgs e)
        {
            valueFirst = decimal.Parse(textBox1.Text);
            textBox1.Clear();
            operators = "*";
        }

        private void percentageBtn_Click(object sender, EventArgs e)
        {
            valueFirst = decimal.Parse(textBox1.Text);
            valueSecond = 7.534m;
            textBox1.Clear();
            Result = valueFirst / valueSecond;
            textBox1.Text = Result.ToString("0.00");
            
        }

        private void equalBtn_Click(object sender, EventArgs e)
        {
            switch (operators)
            {
                case "-":
                    valueSecond = decimal.Parse(textBox1.Text);
                    Result = valueFirst - valueSecond;
                    textBox1.Text = Result.ToString();
                    break;
                case "+":
                    valueSecond = decimal.Parse(textBox1.Text);
                    Result = valueFirst + valueSecond;
                    textBox1.Text = Result.ToString();
                    break;
                case "/":
                    valueSecond = decimal.Parse(textBox1.Text);
                    Result = valueFirst / valueSecond;
                    textBox1.Text = Result.ToString("0.00");
                    break;
                case "*":
                    valueSecond = decimal.Parse(textBox1.Text);
                    Result = valueFirst * valueSecond;
                    textBox1.Text = Result.ToString("0.00");
                    break;
                
            }
        }

        private void ClearBtn_Click(object sender, EventArgs e)
        {
            valueFirst = 0.0m;
            valueSecond = 0.0m;
            textBox1.Text = "0";
        }

        private void Eur_Click(object sender, EventArgs e)
        {
            valueFirst = decimal.Parse(textBox1.Text);
            valueSecond = 7.534m;
            textBox1.Clear();
            Result = valueFirst * valueSecond;
            textBox1.Text = Result.ToString("0.00");
        }

    }
}
