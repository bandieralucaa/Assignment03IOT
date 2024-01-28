package backend2.OLDserial.main;

import javax.swing.*;

import backend2.OLDserial.comm.CommChannel;
import backend2.OLDserial.comm.SerialCommChannel;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Gui {

    private CommChannel commChannel;
    private JFrame frame;
    private JButton btnTurnOn;
    private JButton btnTurnOff;
    private JButton btnGetDistance;  // Modificato il nome del pulsante
    private JLabel distanceLabel;

    public Gui() {
        initialize();
        setupSerialCommunication();
    }

    private void initialize() {
        frame = new JFrame("LED and Sonar Control App");
        frame.setBounds(100, 100, 400, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        frame.getContentPane().add(panel, BorderLayout.CENTER);
        panel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

        btnTurnOn = new JButton("Turn On LED");
        panel.add(btnTurnOn);

        btnTurnOff = new JButton("Turn Off LED");
        panel.add(btnTurnOff);

        btnGetDistance = new JButton("Get Distance");  // Aggiunto il pulsante per ottenere la distanza
        panel.add(btnGetDistance);

        distanceLabel = new JLabel("Distanza: N/D");
        panel.add(distanceLabel);

        btnTurnOn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                sendCommandToArduino("1");
            }
        });

        btnTurnOff.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                sendCommandToArduino("0");
            }
        });

        btnGetDistance.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                sendCommandToArduino("DIST");
            }
        });
    }

    private void setupSerialCommunication() {
        try {
            // Specifica il nome della porta seriale e il tasso di trasmissione (bps)
            String portName = "COM3"; // Modifica il nome della porta seriale in base al tuo ambiente
            int baudRate = 9600;

            commChannel = new SerialCommChannel(portName, baudRate);
        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(frame, "Errore nella configurazione della porta seriale.", "Errore", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
        }
    }

    private void sendCommandToArduino(String command) {
        try {
            // Invia il comando all'Arduino attraverso la porta seriale
            commChannel.sendMsg(command);

            // Se il comando è "DIST", leggi la risposta e aggiorna il JLabel
            if (command.equals("DIST")) {
                String response = commChannel.receiveMsg();
                updateDistanceLabel(response);
            }

            System.out.println("Comando inviato con successo: " + command);
        } catch (Exception e) {
            e.printStackTrace();
            JOptionPane.showMessageDialog(frame, "Errore nell'invio del comando.", "Errore", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void updateDistanceLabel(String response) {
        if (response.startsWith("DIST:")) {
            String distanceStr = response.substring(5);
            distanceLabel.setText("Distanza: " + distanceStr + " cm");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                try {
                    Gui window = new Gui();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
