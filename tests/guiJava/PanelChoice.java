package guiJava;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class PanelChoice implements ActionListener {
    private ButtonGroup group;

    public PanelChoice(JPanel parent, String label, String[] strings,
            int value) {
        parent.add(new JLabel(label));
        group = new ButtonGroup();
        int i = 0;
        for (String string : strings) {
            Boolean val = (i == value ? true : false);
            JRadioButton radioButton = new JRadioButton(string, val);
            radioButton.addActionListener(this);
            group.add(radioButton);
            parent.add(radioButton);
            i++;
        }
    }

    public void actionPerformed(ActionEvent event) {}
}
