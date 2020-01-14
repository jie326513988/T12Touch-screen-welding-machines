void setDispaly()
{
  if (set_display_state == 1)
  {
    show_string("P", 0, 0, 3, fc1, BLACK, 1);
    show_string("I", 117, 0, 3, fc1, BLACK, 1);
    show_string("D", 234, 0, 3, fc1, BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    set_display_state = 0;
  }
  if (keyboard_state == 1)
  {
    keyboard_display();
    keyboard_state = 0;
  }
  if (p_change == 0) show_number_float(1, p, 0, 30, 3, fc2, BLACK  , 0);
  else if (p_change == 1) show_number_float(1, p, 0, 30, 3, WHITE, BLACK  , 0);
  if (i_change == 0)  show_number_float(1, i, 117, 30, 3, fc2, BLACK  , 0);
  else if (i_change == 1)  show_number_float(1, i, 117, 30, 3, WHITE, BLACK  , 0);
  if (d_change == 0)  show_number_float(1, d, 233, 30, 3, fc2, BLACK  , 0);
  else if (d_change == 1)  show_number_float(1, d, 233, 30, 3, WHITE, BLACK  , 0);
}

void keyboard_display()
{
  //mylcd.Set_Draw_color(WHITE);
  //mylcd.Fill_Rectangle( keyboard_x,  keyboard_y + 23, keyboard_x + 170,  keyboard_y - 105);

  show_string("1", keyboard_x, keyboard_y, 3, fc3 , WHITE, 1);
  show_string("2", keyboard_x + 50, keyboard_y, 3, fc3, WHITE, 1);
  show_string("3", keyboard_x + 100, keyboard_y, 3, fc3, WHITE, 1);
  show_string("<", keyboard_x + 150, keyboard_y , 3, fc3, WHITE, 1);

  show_string("4", keyboard_x , keyboard_y - 50, 3, fc3, WHITE, 1);
  show_string("5", keyboard_x + 50, keyboard_y - 50, 3, fc3, WHITE, 1);
  show_string("6", keyboard_x + 100, keyboard_y - 50, 3, fc3, WHITE, 1);
  show_string("0", keyboard_x + 150, keyboard_y - 50, 3, fc3, WHITE, 1);

  show_string("7", keyboard_x , keyboard_y - 100, 3, fc3, WHITE, 1);
  show_string("8", keyboard_x + 50, keyboard_y - 100, 3, fc3, WHITE, 1);
  show_string("9", keyboard_x + 100, keyboard_y - 100, 3, fc3, WHITE, 1);
  if (dotFlag == 0) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, fc3, BLACK, 0);
  else if (dotFlag == 1) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, WHITE, BLACK , 0);
  show_string("Ok", keyboard_x + 135, keyboard_y - 129, 3, fc3, BLACK, 1);
}
