import java.util.Scanner;

public class Game {

    private Player human;
    private Player cpu;    

    public Game() {

        human = new Human();
        cpu = new Computer();

    }


    public void play() {

        //instantiate scanner to use throughout play
        Scanner in = new Scanner(System.in);
        //start the game
        initialize(in);

        int r = 0;
        while(!hasWon()) {

            System.out.println("\n\nRound " + ++r);
            
            Avatar av = selectAvatar(in);
            int act = selectAction(in, av);
            Avatar tar = selectTarget(in);

            int x = (int) Math.random() < 0.5 ? 0 : 1;
            if(av.compareTo(tar) == 1 || (av.compareTo(tar) == 0 && x == 1)) {
                ((Human)human).move(av, act, tar);
                System.out.println(av.getStats() + "\n" + cpu.getAvatar(0).getStats()); //put these in the Player or Avatar class isntead (should directly correlate with the action)
                if(hasWon()) 
                    break;
                ((Computer)cpu).move(av);           
            } else {
                ((Computer)cpu).move(av);
                System.out.println(av.getStats() + "\n" + cpu.getAvatar(0).getStats());
                if(hasWon())
                    break;
                ((Human)human).move(av, act, tar);
            }
            
            System.out.println(av.getStats() + "\n" + cpu.getAvatar(0).getStats());            

        }

    }


    private void initialize(Scanner in) {

        System.out.println("Welcome to Simple RPG!\nWhat is your name?");
        String name = in.nextLine();
        human.setName(name);
        System.out.println("Welcome, " + human.getNmae() + "!");

    }


    private boolean hasWon() { 

        if(!cpu.hasAvatars()) {
            System.out.println(human + " won!");
            return true;
        } else if(!human.hasAvatars()) {
            System.out.println(cpu + " won!");
            return true;
        } else {
            return false;
        }
        
    }


    private Avatar selectAvatar(Scanner in) {

        int av;
        while(true) {
            System.out.println("Which avatar to do you want to play?" + 
                "(Select the Avatar's number)\n" + ((Human)human).showAvatars());
            av = in.nextInt();
            if(av < 1 || av > 3)
                System.out.println("Invalid entry.");
            else
                break;
        }

        return human.getAvatar(av-1);

    }


    private int selectAction(Scanner in, Avatar av) {

        int act;
        while(true) {
            System.out.println("Which action do you want to play? (Select the action number)\n" + 
                av + ":\n" + av.showActions());
            act = in.nextInt();
            if(act < 1 || act > 3)
                System.out.println("Invalid entry.");
            else
                break;
        }
        
        return act;

    }


    private Avatar selectTarget(Scanner in) {

        int tar;
        while(true) {
            System.out.println("Which avatar do you want to target? (Select by number)\n" + 
                ((Human)human).showAvatars() + "\n" + ((Computer)cpu).showAvatars());
            tar = in.nextInt();
            if(tar < 1 || tar > 4)
                System.out.println("Invalid entry");
            else
                break;
        }

        return (tar == 4 ? cpu.getAvatar(0) : human.getAvatar(tar-1));

    }    


}