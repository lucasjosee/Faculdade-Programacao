public class main
{
    public static int inicio; //Variavel global para manipular a linha de entrada

    public static void main(String[] args)
    {
        String linha;
        String informacao;

       for (int i = 0; i < linha.length(); i++)
        {
        
        if (linha.charAt(i) == ',') 
        {
            break;
        } 
        else 
        {
            informacao += linha.charAt(i);
        }
        }
    }

    public static String proximoCampo(String linha) 
    {
        String informacao = "";

        int i = 0;
        for (i = inicio; i < linha.length(); i++)
        {
            if (linha.charAt(i) == ',') 
            {
                break;
            } 
            else 
            {
                informacao += linha.charAt(i);
            }
        }
        inicio += (i + 1);

        return informacao;
    }
}

class Game
{
    //Atributos
    private int id;
    private String name;
    private String releasedate;
    private int estimetedOwners;
    private float price;
    private String[] supportedlanguages;
    private int metacriticScore;
    private float userScore;
    private int achievements;
    private String[] publishers;
    private String[] developers;
    private String[] categories;
    private String[] genres;
    private String[] tags;

    //Construtor

    public Game()
    {

    }

    public Game(int id, String name, String releasedate, int estimetedOwners, float price, String[] supportedlanguages, int metacriticScore, float userScore, int achievements, String[] publishers, String[] developers, String[] categories, String[] genres, String[] tags)
    {
        this.id = id;
        this.name = name;
        this.releasedate = releasedate;
        this.estimetedOwners = estimetedOwners;
        this.price = price;
        this.supportedlanguages =supportedlanguages;
        this.metacriticScore = metacriticScore;
        this.userScore = userScore;
        this.achievements = achievements;
        this.publishers = publishers;
        this.developers = developers;
        this.categories = categories;
        this.genres = genres;
        this.tags = tags;
    }

    //Getters e Setters

    //id
    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    //releaseDate
    public String getReleaseDate() { return releaseDate; }
    public void setReleaseDate(String releaseDate) { this.releaseDate = releaseDate; }
    //estimatedOwners
    public int getEstimatedOwners() { return estimatedOwners; }
    public void setEstimatedOwners(int estimatedOwners) { this.estimatedOwners = estimatedOwners; }
    //price
    public float getPrice() { return price; }
    public void setPrice(float price) { this.price = price; }
    //supportedLanguages
    public String[] getSupportedLanguages() { return supportedLanguages; }
    public void setSupportedLanguages(String[] supportedLanguages) { this.supportedLanguages = supportedLanguages; }
    //metacriticScore
    public int getMetacriticScore() { return metacriticScore; }
    public void setMetacriticScore(int metacriticScore) { this.metacriticScore = metacriticScore; }
    //userScore
    public float getUserScore() { return userScore; }
    public void setUserScore(float userScore) { this.userScore = userScore; }
    //achievements
    public int getAchievements() { return achievements; }
    public void setAchievements(int achievements) { this.achievements = achievements; }
    //publishers
    public String[] getPublishers() { return publishers; }
    public void setPublishers(String[] publishers) { this.publishers = publishers; }
    //developers
    public String[] getDevelopers() { return developers; }
    public void setDevelopers(String[] developers) { this.developers = developers; }
    //categories
    public String[] getCategories() { return categories; }
    public void setCategories(String[] categories) { this.categories = categories; }
    //genres
    public String[] getGenres() { return genres; }
    public void setGenres(String[] genres) { this.genres = genres; }
    //tags
    public String[] getTags() { return tags; }
    public void setTags(String[] tags) { this.tags = tags; }
}