#include "card.h"

void Card::initialize(Ui::MainWindow *ui_ptr)
{
    ui = ui_ptr;
    checkbox_map =
    {
        {1, ui->cardCheckBox_1},
        {2, ui->cardCheckBox_2},
        {3, ui->cardCheckBox_3},
        {4, ui->cardCheckBox_4},
        {5, ui->cardCheckBox_5},
        {6, ui->cardCheckBox_6},
        {7, ui->cardCheckBox_7},
        {8, ui->cardCheckBox_8},
        {9, ui->cardCheckBox_9},
        {10, ui->cardCheckBox_10},
        {11, ui->cardCheckBox_11},
        {12, ui->cardCheckBox_12},
        {13, ui->cardCheckBox_13},
        {14, ui->cardCheckBox_14},
        {15, ui->cardCheckBox_15},
        {16, ui->cardCheckBox_16}
    };
}
void Card::disable_cards(uint card1, uint card2)
{
    //disable card
    checkbox_map[card1]->setChecked(true);
    checkbox_map[card1]->setEnabled(false);

    checkbox_map[card2]->setChecked(true);
    checkbox_map[card2]->setEnabled(false);
};

void Card::change_card_availability(bool state)
{
    for(int index=1; index<17; index++)
    {
        checkbox_map[index] ->setCheckable(state);
    }
}

bool Card::is_matched_cards(uint card1, uint card2)
{
    //compare card if match
    if (checkbox_map[card1]->styleSheet() == checkbox_map[card2]->styleSheet())
    {
        return true;
    }
    return false;
}

void Card::card_handler(uint cardId, bool status)
{
    qDebug("card_handler");
    if(status == true) // card is opened
    {
        num_opened_cards++;
        if(pre_opened_card_id != 0 && num_opened_cards > 1)
        {
            if(is_matched_cards(pre_opened_card_id, cardId))
            {
                disable_cards(pre_opened_card_id, cardId);
            }
            else
            {
                checkbox_map[pre_opened_card_id] ->setChecked(false);
                checkbox_map[cardId] ->setChecked(false);
            }
            pre_opened_card_id = 0;
            num_opened_cards = 0;
            return;
        }
        pre_opened_card_id = cardId;
    }
    else // close a card
    {
        num_opened_cards--;
        pre_opened_card_id= 0;
    }
}

void Card::add_random_images()
{
    // todo: randomly add 8 images to 16 checkboxes
    // the idea should be: 1, Create an Qstring array of 16 items, goes from card_1.jpg, card_1.jpg, card_2.jpg, card_2.jpg,... to card_8.jpg
    //                     2, Shuffle the array
    //                     3, Add each array item to the styleSheet

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    QString defaultStyleSheet = "QCheckBox {spacing: 5px;}"
                                "QCheckBox::indicator {width: 150px; height: 150px;}"
                                "QCheckBox::indicator:unchecked {image: url(:cardBack.jpg);}";

    // step 1

    for (int i = 0; i < 8; i++)
    {
        appendStyleSheet[2*i]   = "QCheckBox::indicator:checked {image: url(:card_" + QString::number(i+1) + ".jpg);}";
        appendStyleSheet[2*i+1] = "QCheckBox::indicator:checked {image: url(:card_" + QString::number(i+1) + ".jpg);}";
    }

    qDebug("---styleSheet before shuffle---");
    for (int i = 0; i < 16; i++)
    {
       qDebug() << "index: " << i << appendStyleSheet[i];
    }

    // Step 2

    shuffle(appendStyleSheet.begin(), appendStyleSheet.end(), std::default_random_engine(seed));

    qDebug("---styleSheet after shuffle---");
    for (int i = 0; i < 16; i++)
    {
       qDebug() << "index: " << i << appendStyleSheet[i];
    }

    // Step 3 (need to find a quicker way to do this -> DONE!)

    for (int i = 1; i < 17; i++)
    {
       checkbox_map[i] ->setStyleSheet(defaultStyleSheet + appendStyleSheet[i-1]);
    }
}
