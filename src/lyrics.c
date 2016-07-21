#include "lyrics.h"

void chooseLyrics(TextLayer *s_lyrics_layer, int dayOfYear)
{
	dayOfYear = dayOfYear % 31;    // <--number based on number of lyrics in system    (the last case + 1)
	
    switch (dayOfYear)
    {
        default:
            text_layer_set_text(s_lyrics_layer, "Sometimes to stay alive, you've gotta kill your mind");
            break;
        case 1:
            text_layer_set_text(s_lyrics_layer, "Sometimes quiet is violent");
            break;
        case 2:
            text_layer_set_text(s_lyrics_layer, "But you specialize in dying, You hear me screaming Father");
            break;
        case 3:
            text_layer_set_text(s_lyrics_layer, "Faith is to be awake, and to be awake is for us to think");
            break;
        case 4:
            text_layer_set_text(s_lyrics_layer, "Somebody stole my car radio and now I just sit in silence");
            break;
        case 5:
            text_layer_set_text(s_lyrics_layer, "My lungs will fill and then deflate. They fill with fire, exhale desire.");
            break;
        case 6:
            text_layer_set_text(s_lyrics_layer, "Stay alive");
            break;
        case 7:
            text_layer_set_text(s_lyrics_layer, "We're broken people");
            break;
        case 8:
            text_layer_set_text(s_lyrics_layer, "I'll put you on the map, I'll cure you of disease");
            break;
        case 9:
            text_layer_set_text(s_lyrics_layer, "Some see a pen, I see a harpoon");
            break;
        case 10:
            text_layer_set_text(s_lyrics_layer, "I don't want to be heard. I want to be listened to");
            break;
        case 11:
            text_layer_set_text(s_lyrics_layer, "Power to the local dreamer");
            break;
        case 12:
            text_layer_set_text(s_lyrics_layer, "Peace will win and fear will lose");
            break;
        case 13:
            text_layer_set_text(s_lyrics_layer, "I'm forced to deal with what I feel. There's no distraction to mask what is real.");
            break;
        case 14:
            text_layer_set_text(s_lyrics_layer, "And once again, I will be on a march to the sea");
            break;
        case 15:
            text_layer_set_text(s_lyrics_layer, "The sun will rise and we will try again");
            break;
        case 16:
            text_layer_set_text(s_lyrics_layer, "I'll stay awake, because the dark's not taking prisoners tonight");
            break;
        case 17:
            text_layer_set_text(s_lyrics_layer, "He is waiting, oh so patiently, while we repeat the same routine as we will please comfortability");
            break;
        case 18:
            text_layer_set_text(s_lyrics_layer, "And I'm lying here just crying, so wash me with your water");
            break;
        case 19:
            text_layer_set_text(s_lyrics_layer, "I know my soul's freezing. Hell's hot for good reason");
            break;
        case 20:
            text_layer_set_text(s_lyrics_layer, "You're the judge, oh no, set me free");
            break;
        case 21:
            text_layer_set_text(s_lyrics_layer, "I'm a goner. Somebody catch my breath.");
            break;
        case 22:
            text_layer_set_text(s_lyrics_layer, "It ain't the speakers that bump hearts, it's our hearts that make the beat");
            break;
        case 23:
            text_layer_set_text(s_lyrics_layer, "Where we're from, we're no one, Our hometown's in the dark");
            break;
        case 24:
            text_layer_set_text(s_lyrics_layer, "Am I the only one I know, waging my wars behind my face and above my throat?");
            break;
        case 25:
            text_layer_set_text(s_lyrics_layer, "No one looks up anymore, cause you might get a raindrop in your eye");
            break;
        case 26:
            text_layer_set_text(s_lyrics_layer, "I've been thinking too much");
            break;
        case 27:
            text_layer_set_text(s_lyrics_layer, "My name is Blurryface and I care what you think");
            break;
        case 28:
            text_layer_set_text(s_lyrics_layer, "Our brains are sick, but that's okay");
            break;
        case 29:
            text_layer_set_text(s_lyrics_layer, "Domingo en fuego, I think I lost my halo");
            break;
        case 30:
            text_layer_set_text(s_lyrics_layer, "You would do almost anything just to feel free");
            break;
    }
}