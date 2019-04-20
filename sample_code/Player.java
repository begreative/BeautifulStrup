import java.util.Arrays;

public class Player {


    protected Avatar[] avatars;
    protected String name;


    public void setName(String n) { name = n; }


    public String getNmae() { return name; }


    public boolean hasAvatars() {

        updateAvatars();
        for(Avatar a: avatars)
            if(a != null)
                return true;

        return false;
        
    }


    public Avatar getAvatar(int av) { return avatars[av]; }


    private void updateAvatars() {

        for(int i = 0; i < avatars.length; i++)
            if(avatars[i].getHP() <= 0)
                avatars[i] = null;

    }


    public String toString() { return name; }


}



class Human extends Player {

    public Human() {

        avatars = new Avatar[]{ new Wizard(), new Fighter(), new Archer() };
        name = null;

    }


    public String showAvatars() {

        String avs = "";
        for(int i = 0; i < avatars.length; i++) {
            if(avatars[i] != null)
                avs += avatars[i] + " [" + (i+1) + "]";
            if(i < avatars.length-1)
                avs += "\n";
        }

        return avs;  
                  
    }


    public void move(Avatar av, int act, Avatar tar) {

        int i = Arrays.asList(avatars).indexOf(av);
        if(i > -1) {
            avatars[i].doAction(act, tar);
        }     

    }


}



class Computer extends Player {

    public Computer() {

        avatars = new Avatar[] { new Dragon() };
        name = "Computer";

    }

    public String showAvatars() { return (avatars[0] + " [" + 4 + "]"); }


    public void move(Avatar tar) {

        int act = (int)(Math.random() * (3 - 1) + 1);
        if(avatars[0] != null) {
            avatars[0].doAction(act, tar);
        }


    }

}