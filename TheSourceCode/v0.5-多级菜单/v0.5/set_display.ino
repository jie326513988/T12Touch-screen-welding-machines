void setDispaly()
{
  if (set_display_state == 1)
  {
    if (p_change == 0) show_string("P", 30, 0, 3, RED, BLACK, 1);
    else if (p_change == 1) show_string("P", 30, 0, 3, WHITE , BLACK, 1);

    if (i_change == 0) show_string("I", 150, 0, 3, RED, BLACK, 1);
    else if (i_change == 1) show_string("I", 150, 0, 3, WHITE , BLACK, 1);

    if (d_change == 0) show_string("D", 270, 0, 3, RED, BLACK, 1);
    else if (d_change == 1) show_string("D", 270, 0, 3, WHITE , BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    set_display_state = 0;
  }
  if (keyboard_state == 1)
  {
    keyboard_display();
    keyboard_state = 0;
  }
  show_number_float(1, p, 5, 30, 3, BLUE, BLACK  , 0);
  show_number_float(1, i, 135, 30, 3, BLUE, BLACK  , 0);
  show_number_float(1, d, 250, 30, 3, BLUE, BLACK  , 0);
}

void keyboard_display()
{
  show_string("1", keyboard_x, keyboard_y, 3, RED, WHITE, 0);
  show_string("2", keyboard_x + 50, keyboard_y, 3, RED, WHITE, 0);
  show_string("3", keyboard_x + 100, keyboard_y, 3, RED, WHITE, 0);
  show_string("<", keyboard_x + 150, keyboard_y , 3, RED, WHITE, 0);

  show_string("4", keyboard_x , keyboard_y - 50, 3, RED, WHITE, 0);
  show_string("5", keyboard_x + 50, keyboard_y - 50, 3, RED, WHITE, 0);
  show_string("6", keyboard_x + 100, keyboard_y - 50, 3, RED, WHITE, 0);
  show_string("0", keyboard_x + 150, keyboard_y - 50, 3, RED, WHITE, 0);

  show_string("7", keyboard_x , keyboard_y - 100, 3, RED, WHITE, 0);
  show_string("8", keyboard_x + 50, keyboard_y - 100, 3, RED, WHITE, 0);
  show_string("9", keyboard_x + 100, keyboard_y - 100, 3, RED, WHITE, 0);
  if (dotFlag == 0) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, RED, WHITE, 0);
  else if (dotFlag == 1) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, RED, BLACK, 0);
  show_string("Ok", keyboard_x + 190, keyboard_y - 100, 3, RED, WHITE, 0);
}
