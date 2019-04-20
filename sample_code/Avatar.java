public class Avatar implements Comparable<Avatar> {


    protected int hp, defense, speed, dot, counter;
    protected String type;
    protected String[] actions;
    

    protected Avatar() { dot = counter = 0; }


    public int getHP() { return hp; }


    protected int getDef() { return defense; }


    protected void updateHP(int amt) { hp += amt; }


    protected void updateDefense(int amt) { defense += amt; }


    protected void updateSpeed(int amt) { speed += amt; }


    public void setDOT(int amt) { 

        counter = 3;
        dot = amt; 
    
    }


    protected void takeDOT() {

        if(counter-- > 0)
            hp -= dot;

    }


    public String showActions() {

        String acts = "";
        for(int i = 0; i < actions.length; i++) {
            acts += actions[i] + " [" + (i+1) + "]";
            acts += i == actions.length-1 ? "" : "\n";
        }            
        
        return acts;

    }


    public void doAction(int act, Avatar av) { }


    public String getStats() { return "HP=" + hp + " | Def=" + defense + " | Speed=" + speed; }


    public String toString() { return type; }

    
    public int compareTo(Avatar av) {

        if(this.speed > av.speed)
            return 1;
        else if(this.speed < av.speed)
            return -1;
        else
            return 0;

    }


}


class Wizard extends Avatar {

    public Wizard() {

        super();
        hp = 500;
        defense = 80;
        speed = 40;
        type = "Wizard";
        actions = new String[]{ "Fireball", "Shield", "Heal"};

    }

    @Override
    public void doAction(int act, Avatar av) {

        takeDOT();

        boolean success = false;
        if(act == 1) {
            int attack = 70;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            attack = 10;
            damage = (attack  * attack/(attack + av.getDef()));
            av.setDOT(damage);
            success = true;
        } else if(act == 2) {
            av.updateDefense(10);
            success = true;
        } else if(act == 3) {
            av.updateHP(20);
            av.setDOT(0);
            success = true;
        }

        if(success)
            System.out.println("\n" + type + " did " + actions[act-1] + " on " + av + "!");

    }

}



class Fighter extends Avatar {


    public Fighter() {

        super();
        hp = 650;
        defense = 50;
        speed = 60;
        type = "Fighter";
        actions = new String[]{ "Slash", "Parry", "Roar"};

    }


    @Override
    public void doAction(int act, Avatar av) {

        takeDOT();

        boolean success = false;
        if(act == 1) {
            int attack = 120;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            success = true;
        } else if(act == 2) {
            defense += 5;
            int attack = 30;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            success = true;
        } else if(act == 3) {
            av.updateDefense(-5);
            success = true;
        }

        if(success)
            System.out.println("\n" + type + " did " + actions[act-1] + " on " + av + "!");

    }


}


class Archer extends Avatar {


    public Archer() {

        super();
        hp = 575;
        defense = 35;
        speed = 80;
        type = "Archer";
        actions = new String[]{ "Shoot Arrow", "Poison Arrow", "Dodge"};

    }


    @Override
    public void doAction(int act, Avatar av) {

        takeDOT();
        
        boolean success = false;
        if(act == 1) {
            int odds = (int) (Math.random() * 100 + 1);
            int attack = odds <= 25 ? 120 : 40;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            success = true;
        } else if(act == 2) {
            int attack = 50;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            av.updateSpeed(-10);
            success = true;
        } else if(act == 3) {
            speed += 5;
            defense += 5;
            success = true;
        }

        if(success)
            System.out.println("\n" + type + " did " + actions[act-1] + " on " + av + "!");

    }
    

}


class Dragon extends Avatar {


    public Dragon() {

        super();
        hp = 2000;
        defense = 100;
        speed = 100;
        type = "Dragon";
        actions = new String[]{ "Fire Breath", "Wing Flap", "Fly"};

    }


    public void doAction(int act, Avatar av) {

        takeDOT();
        
        boolean success = false;
        if(act == 1) {
            int attack = 100;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            attack = 30;
            damage = (attack  * attack/(attack + av.getDef()));
            av.setDOT(damage);
            success = true;
        } else if(act == 2) {
            int attack = 20;
            int damage = (attack  * attack/(attack + av.getDef())) * -1;
            av.updateHP(damage);
            av.updateSpeed(-5);
            success = true;
        } else if(act == 3) {
            hp += 10;
            speed += 5;
            success = true;
        }

        if(success)
            System.out.println("\n" + type + " did " + actions[act-1] + " on " + av + "!");

    }
    

}