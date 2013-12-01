public class WelcomeUserAction{
 
	private String username;
	private String password;
	
	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getUsername() {
		return username;
	}
 
	public void setUsername(String username) {
		this.username = username;
	}
 
	// all struts logic here
	public String execute() {
        WelcomeUserAction wobj = new WelcomeUserAction();
        wobj.setUsername(username);
        wobj.setPassword(password);
        System.out.println("Username is ***************:  "+wobj.getUsername());
        System.out.println("Username is ***************:  "+wobj.getPassword());
        //Enter database code to match user name and password and remove below written logic
        if(wobj.getUsername().length()==0|!(wobj.getUsername().contentEquals(wobj.getPassword()))){
        	System.out.println("in here");
        	return "FAILURE";
        }
        System.out.println("here");
		return "SUCCESS";
 
	}
}

