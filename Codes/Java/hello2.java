import javax.swing.*;

void main() {
    JFrame frame = new JFrame("Java");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 200);

    JLabel label = new JLabel("Oi Java!", SwingConstants.CENTER);
    frame.getContentPane().add(label);

    frame.setVisible(true);

    IO.println("Rodando numa boa!");
}
