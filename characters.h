
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
using namespace std;

class Explorer_Animation_Shift //This class will make the texture shift. 
{
private:
	void next_movement()
	{
		if (++index_character_frame >= character_max_animation)
		{
			index_character_frame = 0; // will reset if the i in the animation process exceeded character max animation. This is just for safety measures.
		}
	}
	static constexpr float  hold_animation_time = 0.1f;//how fast will each image stay before shuffling to the next image. The lower, the better.
	static constexpr int character_max_animation = 8;//this is the character frames that will be shuffled or the maximum  animation it can do. 
	sf::IntRect characterFrames[character_max_animation];
	int index_character_frame = 0; //Current frame in the picture.
	float current_time = 0.0f;

public:
	sf::Texture explorer_texture;
	Explorer_Animation_Shift() = default;
	Explorer_Animation_Shift(int x, int y, int width, int height)
	{
		explorer_texture.loadFromFile("EXPLORER.png");
		for (int i = 0; i < character_max_animation; i++)//says that if i is less than the characterFrames, add only 1 until 7. Will proceed only on 7. 
		{
			characterFrames[i] = { x + i * width,y,width,height };
			//x+i* width is the shuffler!. Must divide pixels by number of frames on x. It will be inputted to character frame 1 and so on until 7. 
			// y will only change depending on the position of the character positions in the image
			//width is consistent and will make IntRec consistent at 64 pixels of width only. Same goes with height.
		}
	}
	void explorer_shifting_frame(sf::Sprite& explorer)
	{
		explorer.setTextureRect(characterFrames[index_character_frame]); //Per frame, the cut of the pixel. This code is the starting frame. 
		explorer.setTexture(explorer_texture);
	}
	void updateTime(float deltatime)
	{
		current_time = current_time + deltatime;//the current time is equal to time plus delta time.
		while (current_time >= hold_animation_time)//will always be true because of the equation above. 
		{
			current_time = current_time - hold_animation_time;//infinite loop forever where it would reset the time back to one again while on while function.
			next_movement();//would reset every frames to zero thus restarting again from the first frame. 
		}

	}
};
class Explorer_Movement //This class will make the sprite move with the shifting texture. 
{
private:
	enum class direction_index
	{
		walkUp,
		walkDown,
		walkLeft,
		walkRight,
		Count // Count will count how many enum class there is. In this case, there are 4 or the directions.
	};
	static constexpr float speed = 100.0f;
	sf::Vector2f position; //Vector for the position
	sf::Vector2f velocity; //Vector for the velocity
	sf::Sprite explorer;
	Explorer_Animation_Shift movement[int(direction_index::Count)];//will function as the current enum values even without typing it all into a specific variable name. This array references all the values from animationPositionIndex
	direction_index current_animation = direction_index::walkLeft;

public:
	Explorer_Movement(const sf::Vector2f& position, sf::Sprite& explorer)
		:position(position), explorer(explorer)
	{
		explorer.setTextureRect({ 0,0,64,64 });//= this is the area of the sprite's shuffling of each specific frame. This is the constructor. 
		movement[int(direction_index::walkUp)] = Explorer_Animation_Shift(64, 128, 64, 64); //Calls the class that makes the texture move. 
		movement[int(direction_index::walkDown)] = Explorer_Animation_Shift(64, 0, 64, 64);
		movement[int(direction_index::walkLeft)] = Explorer_Animation_Shift(64, 64, 64, 64);
		movement[int(direction_index::walkRight)] = Explorer_Animation_Shift(64, 192, 64, 64);
	}
	void ShiftingandDraw(sf::RenderTarget& drawImage) //will render the target and draw. Important for it renders and opens the black scren for rendering of images.
	{
		drawImage.draw(explorer);
	}
	void setDirections(const sf::Vector2f& direction) //boolean, if true or false. 
	{
		velocity = direction * speed;//Allows the picture to move depending on the keyboard direction and speed.
		if (direction.y > 0.0f) // if the y direction is greater than 0, go to Up! In SFML, y axis increases downwards.
		{
			current_animation = direction_index::walkUp;
		}
		else if (direction.y < 0.0f) // if the y direction is lesser than 0, go to Down! In SFML, y axis decreases upwards.
		{
			current_animation = direction_index::walkDown;
		}
		else if (direction.x < 0.0f)
		{
			current_animation = direction_index::walkLeft;
		}
		else if (direction.x > 0.0f)
		{
			current_animation = direction_index::walkRight;
		}
	}
	void updatePositionAllOver(float deltatime)
	{
		position += velocity * deltatime; // will update the position of the frames in the area of the console. Velocity is multiplied to deltatime to shift the position based on time and would restart again each second or so.
		movement[int(current_animation)].updateTime(deltatime); //will call and update the initial time to current time.
		movement[int(current_animation)].explorer_shifting_frame(explorer);
		explorer.setPosition(position); // will overall update the position of the sprite.
		std::cout << explorer.getPosition().y;

	}
	void stopWalk(float deltatime)
	{
		deltatime = 0;
		position += velocity * deltatime; // will update the position of the frames in the area of the console. Velocity is multiplid to deltatime to shift the position based on time and would restart again each second or so.
		movement[int(current_animation)].updateTime(0); //will call and update the initial time to current time.
		movement[int(current_animation)].explorer_shifting_frame(explorer);
		explorer.setPosition(position); // will overall update the position of the sprite.
	}
};


