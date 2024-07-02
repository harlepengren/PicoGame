import PicoGame
import time
import random

def get_color():
    possible_colors = [
    0xdac9, # Red
    0x633c, # Blue
    0xa6e8, # Green
    0xdf28, # Yellow
    0xe23c # Magenta
    ]
    
    random_color = random.randint(0,len(possible_colors)-1)
    
    return possible_colors[random_color]

def generate_enemy():
    return [10,270,get_color()]

def run():
    screen_rate = int(1000/30) #30 fps
    screen = PicoGame.PicoScreen()
    buttons = PicoGame.PicoInput()
    enemies = [[10,270,get_color()]]
    enemy_rate = 5 # Enemies created between 1 and 5 seconds
    
    player_position = [25, 10]
    isJumping = False
    max_jumpHeight = 70
    speed = 2
    player_speed = 4
    
    done = False
    
    last_time = 0
    enemy_ticks_remaining = 10 # Number of ticks until we spawn a new enemy
    
    while not done:
        current_time = time.ticks_ms()
        
        if time.ticks_diff(current_time,last_time) > screen_rate:
            buttons.process_inputs()
            
            # Jump Logic
            if isJumping and player_position[0] < 25:
                player_position[0] = 25
                isJumping = False
            elif isJumping:
                if jumpHeight > 0:
                    player_position[0] += player_speed
                    jumpHeight -= player_speed
                else:
                    player_position[0] -= player_speed
            elif not isJumping and buttons.get_key("A"):
                print("Jump ...")
                isJumping = True
                jumpHeight = max_jumpHeight
                
            
            screen.clear_screen(0)
            
            # Generate enemies
            if enemy_ticks_remaining <= 0:
                enemies.append(generate_enemy())
                enemy_ticks_remaining = random.randrange(1,enemy_rate)*30
            
            # Draw Enemies
            for current_enemy in enemies:
                current_enemy[1] -= speed
                
                if current_enemy[1] < 0:
                    enemies.remove(current_enemy)
                else:
                    screen.draw_rectangle(current_enemy[0],current_enemy[1],current_enemy[0]+30,current_enemy[1]+30,current_enemy[2],True)
             
                
            screen.draw_circle(player_position[0],player_position[1],10,0xffff,True)
            screen.render()
            enemy_ticks_remaining -= 1