using System.Text;

if (!Directory.Exists("data"))
{
    Directory.CreateDirectory("data");
}

var files = Directory.GetFiles("data");
if (files.Length == 0)
{
    Console.WriteLine("Missing data in data/");
    return;
}

static int[][] ReadFile(string path)
{
    return File.ReadAllLines(path).Select(y => y.Split(',', StringSplitOptions.RemoveEmptyEntries).Where(x => int.TryParse(x, out var _)).Select(x => int.Parse(x)).ToArray()).ToArray(); ;
}

var data = ReadFile(files[0]);

foreach (var f in files.Skip(1))
{
    var content = ReadFile(f);
    for (int y = 0; y < content.Length; y++)
    {
        for (int x = 0; x < content[y].Length; x++)
        {
            if (content[y][x] > data[y][x])
            {
                data[y][x] = content[y][x];
            }
        }
    }
}

Console.WriteLine("Cities:");
for (int y = 0; y < data.Length; y++)
{
    for (int x = 0; x < data[y].Length; x++)
    {
        if (data[y][x] == 4)
        {
            Console.WriteLine($"{x} ; {y}");
        }
    }
}

Console.WriteLine("Map:");
foreach (var y in data)
{
    Console.Write(string.Join(",", y));
    Console.WriteLine(",");
}

