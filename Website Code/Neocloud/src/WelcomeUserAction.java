public class WelcomeUserAction{
 
	private String username;
 
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
        System.out.println("Username is ***************:  "+wobj.getUsername().length());
        if(wobj.getUsername().length()==0){
        	System.out.println("in here");
        	return "FAILURE";
        }
        System.out.println("here");
		return "SUCCESS";
 
	}
}

