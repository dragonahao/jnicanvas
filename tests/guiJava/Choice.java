import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Choice implements ActionListener {
    private ButtonGroup group_;

    public Choice(JPanel parent, String label, String[] strings, int value) {
        parent.add(new JLabel(label));
        group_ = new ButtonGroup();
        int i = 0;
        for (String string : strings) {
            Boolean val = (i == value ? true : false);
            JRadioButton radio_button = new JRadioButton(string, val);
            radio_button.addActionListener(this);
            group_.add(radio_button);
            parent.add(radio_button);
            i++;
        }
    }

    public void actionPerformed(ActionEvent event) {
    }
}
