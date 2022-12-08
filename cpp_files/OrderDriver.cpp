
#include "../header_files/Orders.h"

/*Free function of driver class. When invoked, it will create a list of orders, each of a different subclass,
and test several of the features of the OrdersList class, which includes addOrder, remove, and move*/

void testOrderLists() {

    OrderOperation operate;
    OrdersList list;

    cout << "\n------------ ADDING ORDERS --------------\n" << endl;

    list.addOrder(operate.createOrder("deploy"));
    list.addOrder(operate.createOrder("advance"));
    list.addOrder(operate.createOrder("bomb"));
    list.addOrder(operate.createOrder("blockade"));
    list.addOrder(operate.createOrder("airlift"));
    list.addOrder(operate.createOrder("negotiate"));

    cout << "\n------------ DELETING ORDERS -------------\n" << endl;

    list.remove(1);
    list.remove(5);
    list.remove(3);

    cout << "\n------------ MOVING ORDERS -------------\n" << endl;

    list.move(1, 3);
    list.move(2, 1);
    list.move(3, 2);

    cout << "\n------------ COPYING LIST USING COPY C'TOR ------------\n" << endl;

    OrdersList ctorList = OrdersList(list);
    cout << ctorList;

    cout << "\n------------- COPYING LIST USING = OPERATOR --------------\n" << endl;

    OrdersList a;
    a.addOrder(operate.createOrder("deploy"));
    a.addOrder(operate.createOrder("bomb"));
    a = list;
    cout << a;

    cout << "\n------------ EXECUTING ORDERS FROM LIST ------------\n";

    list.executeOrders();

    cout << "\n------------- PRINTING ALL THE LISTS --------------\n";

    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;

    cout << "\n********** PRINTING ALL THE LISTS AGAIN + OPERATIONS **********\n";

    list.addOrder(operate.createOrder("deploy"));
    list.addOrder(operate.createOrder("airlift"));
    ctorList.remove(2);
    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;
}

/*void testOrderExecution()
{
    GameEngine ge;
    Player p1("Player_1", new Hand, &ge);
    Player p2("Player_2", new Hand, &ge);
    Player p3("Player_2", new Hand, &ge);

    ge.addPlayer(&p1);
    ge.addPlayer(&p2);
    ge.addPlayer(&p3);

    Territory t1("Ter_1", "Cont_1", &p1, 0, 0);
    Territory t2("Ter_2", "Cont_1", &p2, 0, 0);
    Territory t3("Ter_3", "Cont_1", &p2, 0, 0);

    p1.addOwnedTerritory(&t1);
    p2.addOwnedTerritory(&t2);
    p3.addOwnedTerritory(&t3);

    p1.getPlayerHand()->add(new Card("bomb"));
    p1.getPlayerHand()->add(new Card("blockade"));
    p1.getPlayerHand()->add(new Card("airlift"));
    p1.getPlayerHand()->add(new Card("diplomacy"));
    p1.getPlayerHand()->add(new Card("reinforcement"));

    //Testing Deploy
    p1.add2ReinforecemntPool(50);
    p1.getPlayerOrdersList()->addOrder(new deploy(&p1, &t1, 20, &ge));
    std::cout << t1.details() << std::endl;
    ge.players[0]->getPlayerOrdersList()->getOrders()[0]->execute();
    std::cout << t1.details() << std::endl;
    std::cout << p1.getPlayerHand();

    //Testing Advance
    t1.addNeighbor(&t2);
    p1.getPlayerOrdersList()->addOrder(new advanceOrder(&p1,&t1,&t2, &p2, 10, &ge));
    t2.setNumberArmies(5);
    std::cout << t2.details();
    ge.players[0]->getPlayerOrdersList()->getOrders()[1]->execute();
    std::cout << t1.details();
    std::cout << t2.details();
    std::cout << "since p1 gains ownership, it draws a card.\n";
    std::cout << *p1.getPlayerHand() << std::endl
        ;
    //Testing bomb
    t3.addNeighbor(&t1);
    p3.getPlayerHand()->add(new Card("bomb"));
    p1.getPlayerOrdersList()->addOrder(new bomb(&p3, &t1, ge.getDeck(), &ge));
    cout << t1.details();
    ge.players[0]->getPlayerOrdersList()->getOrders()[2]->execute();
    cout << t1.details();

    //Testing Airlift
    p1.getPlayerOrdersList()->addOrder(new airlift(&p1, &t1, &t2, 2, ge.getDeck(), &ge));
    cout << t1.details();
    cout << t2.details();

    ge.players[0]->getPlayerOrdersList()->getOrders()[3]->execute();

    cout << t1.details() << t2.details() << endl;
    cout << t2.details() << endl;

    //Testing Blockade
    Player np("NeutralPlayer");
    ge.addPlayer(&np);
    p1.getPlayerOrdersList()->addOrder(new blockade(&p1,&t1,ge.getDeck(), &np, &ge));
    ge.players[0]->getPlayerOrdersList()->getOrders()[4]->execute();
    cout << t1.details() << endl;

    //Testing Negotiate
    p1.getPlayerHand()->add(new Card("diplomacy"));
    p1.getPlayerOrdersList()->addOrder(new negotiate(&p1, &p3, ge.getDeck(), &ge));
    ge.players[0]->getPlayerOrdersList()->getOrders()[5]->execute();

    cout << "\n ---- now lets try invalid orders ---\n\n";
    p2.getPlayerOrdersList()->addOrder(new deploy());
    p2.getPlayerOrdersList()->addOrder(new advanceOrder());
    p2.getPlayerOrdersList()->addOrder(new bomb());
    p2.getPlayerOrdersList()->addOrder(new airlift());
    p2.getPlayerOrdersList()->addOrder(new blockade());
    p2.getPlayerOrdersList()->addOrder(new negotiate());

    p2.getPlayerOrdersList()->executeOrders();

}*/